# Draws docs/diagrams/use-case.png (UML use case diagram for the Online Quiz System).
# Run from this folder:  python usecase.py
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Ellipse, Rectangle, Circle

fig, ax = plt.subplots(figsize=(11.4, 7.2))
ax.set_xlim(0, 11.4)
ax.set_ylim(0, 7.2)
ax.axis("off")

# system boundary
ax.add_patch(Rectangle((2.4, 0.3), 6.2, 6.6, fill=False, lw=1.8))
ax.text(5.5, 6.6, "Online Quiz System", ha="center", fontsize=13, weight="bold")


def actor(x, y, label):
    ax.add_patch(Circle((x, y + 0.75), 0.22, fill=False, lw=1.8))
    ax.plot([x, x], [y + 0.53, y - 0.15], "k", lw=1.8)
    ax.plot([x - 0.4, x + 0.4], [y + 0.35, y + 0.35], "k", lw=1.8)
    ax.plot([x, x - 0.35], [y - 0.15, y - 0.75], "k", lw=1.8)
    ax.plot([x, x + 0.35], [y - 0.15, y - 0.75], "k", lw=1.8)
    ax.text(x, y - 1.05, label, ha="center", fontsize=10.5)


def usecase(x, y, label, w):
    ax.add_patch(Ellipse((x, y), w, 0.7, fc="#eef5ff", ec="black", lw=1.5))
    ax.text(x, y, label, ha="center", va="center", fontsize=9.5)
    return (x, y)


def line(a, b, dashed=False, arrow=False):
    ax.annotate("", xy=b, xytext=a,
                arrowprops=dict(arrowstyle="->" if arrow else "-", lw=1.3,
                                linestyle="--" if dashed else "-", color="black",
                                shrinkA=0, shrinkB=0))


actor(1.1, 3.4, "Quiz Taker")

A, B = 3.7, 7.2
u_start = usecase(A, 5.0, "UC1  Start Quiz", 2.4)
u_ans = usecase(B, 6.0, "UC2  Answer Questions", 2.2)
u_score = usecase(B, 5.0, "UC3  Calculate Score", 2.2)
u_show = usecase(B, 4.0, "UC4  View Result", 2.2)
u_save = usecase(B, 3.0, "UC5  Save Result", 2.2)
u_lb = usecase(A, 2.2, "UC6  View Leaderboard", 2.4)
u_ins = usecase(A, 1.45, "UC7  View Instructions", 2.4)
u_exit = usecase(A, 0.75, "UC8  Exit", 2.4)

# actor associations
for t in (u_start, u_lb, u_ins, u_exit):
    line((1.5, 3.45), (t[0] - 1.18, t[1]))

# Start Quiz includes UC2..UC5
for t in (u_ans, u_score, u_show, u_save):
    line((A + 1.2, 5.0), (B - 1.1, t[1]), dashed=True, arrow=True)
    ax.text((A + 1.2 + B - 1.1) / 2, (5.0 + t[1]) / 2 + 0.1, "«include»",
            ha="center", fontsize=8, style="italic")

# secondary actors (files)
for x, y, label in [(9.95, 6.0, "Question Bank\n(questions.txt)"),
                    (9.95, 2.6, "Results File\n(results.txt)")]:
    ax.add_patch(Rectangle((x - 0.9, y - 0.4), 1.8, 0.8, fc="#fff7e6", ec="black", lw=1.5))
    ax.text(x, y, label, ha="center", va="center", fontsize=9.5)
    ax.text(x, y + 0.58, "«secondary actor»", ha="center", fontsize=8.5, style="italic")

line((B + 1.1, 6.0), (9.05, 6.0))      # Answer Questions - Question Bank
line((B + 1.1, 3.0), (9.05, 2.7))      # Save Result - Results File
line((A + 1.2, 2.2), (9.05, 2.45))     # View Leaderboard - Results File

plt.savefig("use-case.png", dpi=170, bbox_inches="tight", facecolor="white")
