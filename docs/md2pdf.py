"""Convert the project's Markdown documents (SRS, SAD, Test Plan) to PDF.

Usage (from the repo root):  python docs/md2pdf.py
Needs Microsoft Edge or Google Chrome (it prints the page to PDF in headless mode).
Supports the Markdown subset used in these documents: headings, paragraphs,
bold/italic/inline code, bullet lists, tables, fenced code blocks and images.
"""
import base64
import html
import mimetypes
import os
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
JOBS = [
    ("SRS.md", "docs/SRS.pdf"),
    ("docs/SAD.md", "docs/SAD.pdf"),
    ("docs/TEST_PLAN.md", "docs/Test_Plan.pdf"),
]
BROWSERS = [
    r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe",
    r"C:\Program Files\Microsoft\Edge\Application\msedge.exe",
    r"C:\Program Files\Google\Chrome\Application\chrome.exe",
    r"C:\Program Files (x86)\Google\Chrome\Application\chrome.exe",
    "msedge", "google-chrome", "chromium", "chrome",
]
INLINE = re.compile(r"(`[^`]+`|\*\*[^*]+\*\*|\*[^*\s][^*]*\*)")
LINK = re.compile(r"\[([^\]]+)\]\([^)]+\)")

CSS = """
@page { size: A4; margin: 18mm 16mm; }
body { font-family: Calibri, 'Segoe UI', Arial, sans-serif; font-size: 10.5pt; line-height: 1.4; color: #111; }
h1.title { text-align: center; font-size: 22pt; margin: 0 0 10pt; }
h1, h2, h3, h4 { color: #1f3864; margin: 14pt 0 5pt; page-break-after: avoid; }
h1 { font-size: 16pt; } h2 { font-size: 13.5pt; } h3 { font-size: 11.5pt; } h4 { font-size: 10.5pt; }
p { margin: 0 0 6pt; }
ul { margin: 0 0 6pt; padding-left: 20pt; }
table { border-collapse: collapse; width: 100%; margin: 4pt 0 10pt; font-size: 9pt; }
th, td { border: 1px solid #777; padding: 3pt 5pt; vertical-align: top; text-align: left; }
th { background: #d9e2f3; }
tr { page-break-inside: avoid; }
code { font-family: Consolas, 'Courier New', monospace; font-size: 9pt; background: #f3f3f3; padding: 0 2pt; }
pre { font-family: Consolas, 'Courier New', monospace; font-size: 8.5pt; background: #f6f6f6; border: 1px solid #ddd;
      padding: 6pt; margin: 0 0 10pt; white-space: pre-wrap; page-break-inside: avoid; }
img { max-width: 100%; display: block; margin: 6pt auto; }
img.narrow { max-width: 62%; }
"""


def esc(text):
    return html.escape(text, quote=False)


def inline(text):
    text = LINK.sub(r"\1", text)
    out = []
    for part in INLINE.split(text):
        if not part:
            continue
        if part.startswith("`") and part.endswith("`") and len(part) > 2:
            out.append("<code>" + esc(part[1:-1]) + "</code>")
        elif part.startswith("**") and part.endswith("**") and len(part) > 4:
            out.append("<strong>" + esc(part[2:-2]) + "</strong>")
        elif part.startswith("*") and part.endswith("*") and len(part) > 2:
            out.append("<em>" + esc(part[1:-1]) + "</em>")
        else:
            out.append(esc(part))
    return "".join(out)


def split_row(line):
    line = line.strip()
    if line.startswith("|"):
        line = line[1:]
    if line.endswith("|"):
        line = line[:-1]
    return [c.strip() for c in line.split("|")]


def image_tag(alt, rel, base):
    path = os.path.normpath(os.path.join(base, rel))
    if not os.path.exists(path):
        path = os.path.normpath(os.path.join(ROOT, rel))
    mime = mimetypes.guess_type(path)[0] or "image/png"
    data = base64.b64encode(open(path, "rb").read()).decode("ascii")
    cls = ' class="narrow"' if "component" in path else ""
    return f'<img{cls} alt="{esc(alt)}" src="data:{mime};base64,{data}">'


def to_html(src_rel):
    src = os.path.join(ROOT, src_rel)
    base = os.path.dirname(src)
    lines = open(src, encoding="utf-8").read().splitlines()
    out = []
    first_h1 = True
    in_list = False
    i = 0

    def close_list():
        nonlocal in_list
        if in_list:
            out.append("</ul>")
            in_list = False

    while i < len(lines):
        line = lines[i]
        s = line.strip()

        if not s or s == "---" or s.startswith("<!--"):
            close_list()
            i += 1
            continue

        if s.startswith("```"):
            close_list()
            i += 1
            code = []
            while i < len(lines) and not lines[i].strip().startswith("```"):
                code.append(lines[i])
                i += 1
            i += 1
            out.append("<pre>" + esc("\n".join(code)) + "</pre>")
            continue

        m = re.match(r"^(#{1,4})\s+(.*)", s)
        if m:
            close_list()
            level = len(m.group(1))
            if level == 1 and first_h1:
                out.append('<h1 class="title">' + inline(m.group(2)) + "</h1>")
                first_h1 = False
            else:
                out.append(f"<h{level}>" + inline(m.group(2)) + f"</h{level}>")
            i += 1
            continue

        m = re.match(r"^!\[([^\]]*)\]\(([^)]+)\)", s)
        if m:
            close_list()
            out.append(image_tag(m.group(1), m.group(2), base))
            i += 1
            continue

        if s.startswith("|"):
            close_list()
            rows = []
            while i < len(lines) and lines[i].strip().startswith("|"):
                cells = split_row(lines[i])
                is_sep = all(re.fullmatch(r":?-{2,}:?", c) for c in cells if c) and any(cells)
                if not is_sep and any(cells):
                    rows.append(cells)
                i += 1
            if rows:
                n = len(rows[0])
                out.append("<table><thead><tr>" + "".join(f"<th>{inline(c)}</th>" for c in rows[0]) + "</tr></thead><tbody>")
                for r in rows[1:]:
                    r = (r + [""] * n)[:n]
                    out.append("<tr>" + "".join(f"<td>{inline(c)}</td>" for c in r) + "</tr>")
                out.append("</tbody></table>")
            continue

        if re.match(r"^[-*]\s+", s):
            if not in_list:
                out.append("<ul>")
                in_list = True
            out.append("<li>" + inline(re.sub(r"^[-*]\s+", "", s)) + "</li>")
            i += 1
            continue

        close_list()
        indent = len(line) - len(line.lstrip(" "))
        style = f' style="margin-left:{indent * 5}pt;margin-bottom:1pt"' if indent else ""
        out.append(f"<p{style}>" + inline(s) + "</p>")
        i += 1

    close_list()
    return "<!doctype html><html><head><meta charset='utf-8'><style>" + CSS + "</style></head><body>" + "\n".join(out) + "</body></html>"


def find_browser():
    for b in BROWSERS:
        if os.path.isfile(b) or shutil.which(b):
            return b
    sys.exit("No Edge or Chrome found")


def convert(src_rel, dst_rel):
    browser = find_browser()
    tmp = tempfile.mkdtemp()
    try:
        page = os.path.join(tmp, "page.html")
        open(page, "w", encoding="utf-8").write(to_html(src_rel))
        dst = os.path.join(ROOT, dst_rel)
        if os.path.exists(dst):
            os.remove(dst)
        subprocess.run(
            [browser, "--headless=new", "--disable-gpu", "--no-pdf-header-footer",
             "--user-data-dir=" + os.path.join(tmp, "profile"),
             "--print-to-pdf=" + dst, "file:///" + page.replace("\\", "/")],
            check=True, capture_output=True, timeout=180)
        if not os.path.exists(dst):
            sys.exit("PDF was not created: " + dst_rel)
        print(f"{dst_rel}: {os.path.getsize(dst) // 1024} KB")
    finally:
        shutil.rmtree(tmp, ignore_errors=True)


if __name__ == "__main__":
    for s, d in JOBS:
        convert(s, d)
