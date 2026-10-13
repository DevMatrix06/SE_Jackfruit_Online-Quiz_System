# Online Quiz System

A small quiz program that runs in the terminal. You answer multiple-choice questions, get a score at the end, and your result is saved to a leaderboard.

Written in C for the Software Engineering mini-project (Team Jackfruit).

## What it does

- Main menu: Start Quiz, View Leaderboard, Instructions, Exit
- Asks one question at a time (options A to D)
- Shows your score, percentage and Pass/Fail (pass mark is 40%)
- Saves your name and score to `results.txt`
- Shows the leaderboard from the highest score to the lowest

## How to build and run

You need `gcc` and `make` (on Windows, `mingw32-make`).

```
make          # build the program
./quiz        # run it (run from this folder, not from src/)
make test     # run the scoring tests
make clean    # remove built files
```

## Project status

Work in progress (Sprint-1).

| Part | Status |
|---|---|
| Main menu and input checks | Done |
| Scoring and result screen | Done, with unit tests |
| Saving results | Done |
| Quiz questions and answers | Done |
| Leaderboard | Planned for Sprint-2 |

## Folders

| Path | What is in it |
|---|---|
| `src/`, `include/` | The C code |
| `data/questions.txt` | The question bank |
| `tests/` | Unit tests |
| `docs/` | Design document, test plan and diagrams |
| `SRS.md` | Software Requirements Specification |

## Documents

- [SRS: what the program must do](docs/SRS.pdf)
- [SAD: how the program is built](docs/SAD.pdf)
- [Test Plan: how we check it](docs/Test_Plan.pdf)
- [Team tasks](TEAM-TASKS.md)

The same documents are also kept as text: [SRS.md](SRS.md), [docs/SAD.md](docs/SAD.md), [docs/TEST_PLAN.md](docs/TEST_PLAN.md).

## Team

| Name | GitHub | Part |
|---|---|---|
| Tejas | DevMatrix06 | Main menu, build, CI, review |
| Sanjana | SanjanaM-28 | Quiz engine and question bank |
| Vikas | jadarvikas | Scoring and result screen |
| Vaishnavi | crithit538 | Saving results and leaderboard |

## How we work

- Requirements are written as user stories ("As a ..., I want ..., so that ...") and grouped under 6 epics (EPIC-1 to EPIC-6)
- One GitHub issue per requirement, tracked on the project board
- One pull request per issue, raised by the person it is assigned to
- GitHub Actions builds the code on every push and pull request
- The repo owner reviews and merges
