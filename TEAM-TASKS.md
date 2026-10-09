# Team Jackfruit: What You Need To Do

Hi all. The backlog for our Online Quiz System is ready on GitHub. Every requirement from our SRS is now an issue with story points, assigned to the person who owns that SRS section. You're already collaborators on the repo.

- **Board:** https://github.com/users/DevMatrix06/projects/3 (filter by your name to see your issues)
- **Repo:** https://github.com/DevMatrix06/SE_Jackfruit_Online-Quiz_System
- **SRS:** `SRS.md` in the repo. Your code must do what your section says.

**Your job:** build your own issues, open one pull request (PR) per issue, and I (Tejas) review and merge. The brief says the person assigned must raise the PR themselves, so don't send me code to push.

## Dates

| When | What |
|---|---|
| 12 to 16 Oct | Setup and practice: clone the repo, try one small PR |
| 19 to 23 Oct | **Sprint-1**: finish your Sprint-1 issues (1-min demo video at the end) |
| 26 to 30 Oct | **Sprint-2**: finish your Sprint-2 issues (2-min video, docs, code freeze) |

## Code layout (so we don't clash)

The program is in plain C. Each person owns their own files, and nobody edits someone else's file without asking.

| File | Owner | What goes in it |
|---|---|---|
| `src/main.c` | Tejas | Main menu, input validation, navigation, exit, Instructions screen |
| `include/quiz.h`, `src/quiz.c` | Sanjana | `Question` struct, loading questions, running the quiz |
| `include/score.h`, `src/score.c` | Vikas | `Result` struct, scoring, percentage, Pass/Fail, result screen |
| `include/storage.h`, `src/storage.c` | Vaishnavi | Saving to `results.txt`, reading it back, leaderboard |
| `data/questions.txt` | Sanjana | The question bank |
| `Makefile`, `.github/workflows/` | Tejas | Build and GitHub Actions |

**Shared functions:** main.c calls these, so keep the names and signatures exactly like this.

```c
/* quiz.h (Sanjana) */
typedef struct {
    char text[256];
    char options[4][128];
    char correct;              /* 'A'..'D' */
} Question;
int  load_questions(const char *path, Question qs[], int max);  /* returns count, -1 on error */
void run_quiz(const Question qs[], int n, char answers[]);      /* fills answers[i] with 'A'..'D' */

/* score.h (Vikas) */
typedef struct {
    int score, correct, incorrect, total;
    double percent;
    int passed;                /* 1 = Pass, 0 = Fail */
} Result;
Result calculate_result(const Question qs[], const char answers[], int n);
void   show_result(const Result *r);

/* storage.h (Vaishnavi) */
int  save_result(const char *name, const Result *r);   /* 0 ok, -1 error */
void show_leaderboard(void);                            /* reads results.txt, sorted high to low */
```

## Your tasks

### Sanjana (SanjanaM-28): Quiz Engine, SRS 4.2

**Sprint-1**
- REQ-17: load MCQs from `data/questions.txt`, each with exactly one correct answer (3 pts)
- REQ-18: show one question at a time with its options (2 pts)
- REQ-19: accept the answer and reject anything that isn't a valid option (2 pts)
- REQ-20: record the answer before moving on (1 pt)
- REQ-21: go to the next question after a valid answer (1 pt)
- REQ-22: keep going until all questions are done (1 pt)

**Sprint-2**
- NFR-4 Reliability: no crash on bad input or a missing or broken questions file (3 pts)
- TEST-1: run the Test Plan test cases and log pass/fail (5 pts)

### Vikas (jadarvikas): Scoring and Results, SRS 4.3

**Sprint-1**
- REQ-7: compare each answer to the correct option and update the score (2 pts)
- REQ-8: count correct and incorrect answers (1 pt)
- REQ-9: calculate the total score and percentage (2 pts)
- REQ-11: show score, %, and correct/incorrect counts at the end (2 pts)

**Sprint-2**
- REQ-10: Pass/Fail based on a percentage threshold (say 40%; must match the SRS) (2 pts)
- REQ-12: hand the finished result to storage (2 pts)
- NFR-5 Maintainability: keep modules separate and commented (2 pts)
- DEMO-2: 2-minute video of the final product, plus README and docs (2 pts)

### Vaishnavi (crithit538): Result Storage and Leaderboard, SRS 4.4

**Sprint-1**
- REQ-13: save the player name and score to `results.txt` after each quiz (3 pts)

**Sprint-2**
- REQ-14: read saved results back from the file (3 pts)
- REQ-15: show the leaderboard sorted by score, highest first (3 pts)
- REQ-16: no crash when `results.txt` doesn't exist yet (2 pts)
- NFR-1 Performance: everything responds within 1 second (1 pt)
- NFR-2 Security: if the file can't be opened, show a friendly error and never print system paths or details (2 pts)

Every issue on the board has acceptance criteria in its description. Your work is done when it meets them.

## How to do each issue

One-time setup:
```
git clone https://github.com/DevMatrix06/SE_Jackfruit_Online-Quiz_System
cd SE_Jackfruit_Online-Quiz_System
```

For every issue (example: REQ-17):
1. On the board, drag your issue to **In Progress**.
2. Make a branch:
   ```
   git checkout main
   git pull
   git checkout -b REQ-17-load-questions
   ```
3. Write the code (use the Claude prompt below), then check that it builds with `make` and works.
4. Push:
   ```
   git add .
   git commit -m "REQ-17: load questions from file"
   git push -u origin REQ-17-load-questions
   ```
5. On GitHub, click **Compare & pull request**. In the description, write `Closes #<issue number>`, set the reviewer to **DevMatrix06**, and create the PR.
6. If GitHub Actions shows a red X, fix the problem and push again to the same branch.
7. I review and merge. The issue then moves to **Done** by itself.

**Never push straight to `main`.** One issue per PR.

## Prompt for your Claude

Open Claude Code (or Claude chat) inside the cloned repo folder and paste this. Fill in the parts in brackets.

```
I'm [NAME], working on Team Jackfruit's Online Quiz System, a console-based MCQ quiz in plain C.
Read SRS.md in this repo first, especially section [4.2 / 4.3 / 4.4] which I own.

My task right now is issue [REQ-XX]: "[issue title]".
Acceptance criteria: [paste from the GitHub issue].

Rules:
- Only edit my own files: [src/quiz.c + include/quiz.h | src/score.c + include/score.h | src/storage.c + include/storage.h].
- Keep the shared struct and function signatures exactly as in TEAM-TASKS.md (copy below):
  [paste the "Shared functions" code block]
- Plain C (C99), must compile with gcc -Wall with no warnings. Use fgets for input, never gets or unbounded scanf("%s").
- Never crash on bad input or missing files; show a clear message instead.
- Small, commented functions. No extra features beyond the SRS.

Steps:
1. Create the branch [REQ-XX-short-name] from an up-to-date main.
2. Implement only this issue and explain what you changed.
3. Build with make and show me it works (run it, or write a small test).
4. Commit with message "[REQ-XX]: [short description]" and push the branch.
5. Open a PR into main with "Closes #[issue number]" in the description and DevMatrix06 as reviewer
   (use `gh pr create` if gh is installed; otherwise tell me to click "Compare & pull request" on GitHub).
```

Do one issue per Claude session, or tell it "now do REQ-XX" for the next one. Always read what it wrote before you push. You have to explain your part in the demo.

Stuck for more than a day? Tell the group.
