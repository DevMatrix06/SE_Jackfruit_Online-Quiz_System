# Software Architecture and Design Specification

**Project:** Online Quiz System
**Version:** 1.0
**Authors:** Team Jackfruit (Tejas, Sanjana, Vikas, Vaishnavi)
**Date:** 12-10-2026
**Status:** Baseline for Sprint-1

## Revision History

| Version | Date | Author | Change Summary |
|---|---|---|---|
| 1.0 | 12-10-2026 | Team | First complete version, aligned with SRS v1.1 and the code on `main` |

## Approvals

| Role | Name | Signature / Date |
|---|---|---|
| Project Lead / Repo Owner | Tejas | |
| Quiz Engine Owner | Sanjana | |
| Scoring Owner | Vikas | |
| Storage Owner | Vaishnavi | |

---

## 1. Introduction

### 1.1 Purpose
This document specifies the architecture and design of the Online Quiz System, a console-based multiple-choice quiz application written in C. It explains how the requirements in the SRS (v1.1) are realised by components, interfaces and data flows, so that the four team members can implement their modules independently and the result can be tested against the Test Plan.

### 1.2 Scope
It covers the whole application: the main menu and navigation, the quiz engine, scoring and result display, and result storage with the leaderboard. It does not cover deployment (the program is a single local executable) or anything outside the SRS scope such as accounts, networking or a GUI.

### 1.3 Audience
Developers implementing the modules, testers deriving test cases, the course evaluators, and anyone maintaining the project later.

### 1.4 Definitions

| Term | Meaning |
|---|---|
| MCQ | Multiple-choice question with exactly one correct option |
| REQ-n | Functional requirement n in the SRS |
| NFR-n / SEC-n | Non-functional / security requirement in the SRS |
| ADR | Architecture decision record |
| STRIDE | Threat categories: Spoofing, Tampering, Repudiation, Information disclosure, Denial of service, Elevation of privilege |
| Console | Terminal window used for all input and output |

---

## 2. Document Overview

### 2.1 How to use this document
Section 3 describes the architecture (components, pattern, traceability, security). Section 4 describes the detailed design (sequence diagrams, function-level API, error handling, console UX). Developers should read 3.4 and 4.3 before touching a module; testers should read 3.8 and 4.4.

### 2.2 Related documents

| Document | Location |
|---|---|
| Software Requirements Specification v1.1 | `SRS.md` |
| Software Test Plan v1.0 | `docs/TEST_PLAN.md` |
| Requirements Traceability Matrix | SRS Appendix C and Section 3.8 of this document |
| Team task split and shared signatures | `TEAM-TASKS.md` |

---

## 3. Architecture

### 3.1 Goals and Constraints

**Goals**
- Keep the program small, readable and easy to test (a mini-project, Easy tier).
- Let four people work in parallel without editing each other's files (NFR-5).
- Never crash on bad input or a missing file (NFR-4).
- Run offline on any machine with a C compiler.

**Constraints**
- Plain C (C99), built with `gcc -Wall -std=c99`; no third-party libraries.
- Console only, single user, single session; no GUI, no network, no database.
- Persistence is limited to local flat text files.
- The shared function signatures and structs in `quiz.h`, `score.h` and `storage.h` are fixed so that modules can be developed in parallel.

### 3.2 Stakeholders and Concerns

| Stakeholder | Concern |
|---|---|
| Quiz taker | Clear prompts, instant result, no crashes |
| Developers (4) | Modularity, clear ownership, stable interfaces |
| Testers | Observable behaviour, deterministic output, traceable requirements |
| Evaluators | Conformance to SRS, architecture and test documents; evidence of process |

### 3.3 Component (UML) Diagram

![UML component diagram](diagrams/component.png)

*Figure 1: Components, provided interfaces and data stores.*

### 3.4 Component Descriptions

| Component | Files | Responsibility | Provided interface | Uses | Owner |
|---|---|---|---|---|---|
| Menu Controller | `src/main.c` | Shows the menu, validates the menu choice, asks for the player name, routes to features, shows instructions, exits cleanly | none (entry point) | IQuiz, IScore, IStorage | Tejas |
| Quiz Engine | `src/quiz.c`, `include/quiz.h` | Loads the question bank, presents one question at a time, validates and records each answer | **IQuiz**: `load_questions`, `run_quiz` | `data/questions.txt` | Sanjana |
| Scoring Module | `src/score.c`, `include/score.h` | Compares answers with correct options, counts correct/incorrect, computes percentage and Pass/Fail (40%), prints the result screen | **IScore**: `calculate_result`, `show_result` | `Question` type from `quiz.h` | Vikas |
| Result Storage and Leaderboard | `src/storage.c`, `include/storage.h` | Appends `Name,Score` to `results.txt`, reads results back, shows the leaderboard sorted high to low | **IStorage**: `save_result`, `show_leaderboard` | `Result` type from `score.h`, `results.txt` | Vaishnavi |
| Question Bank | `data/questions.txt` | Question text, four options and the correct letter | text file | | Sanjana |
| Results File | `results.txt` (created at run time) | One `Name,Score` line per completed attempt | text file | | Vaishnavi |

The only inter-module dependencies are on the two shared data types: `score.h` includes `quiz.h` (for `Question`) and `storage.h` includes `score.h` (for `Result`). No module calls another module's functions except through the Menu Controller, which orchestrates the flow.

### 3.5 Chosen Architecture Pattern and Rationale

**Pattern: layered architecture in a single process (modular monolith).**

| Layer | Contents | Rule |
|---|---|---|
| Presentation and control | `main.c` | Talks to the user and calls the layers below; contains no scoring or file logic |
| Domain | `quiz.c`, `score.c` | Quiz rules and scoring; no knowledge of the menu |
| Data access | `storage.c`, the two text files | The only code that reads or writes `results.txt` |

**Rationale.** The program has one user, one process and three clearly separated concerns, which maps directly onto the team split. Layering gives each owner a file boundary (so pull requests do not clash), makes each module testable on its own (`tests/test_score.c` links only `score.c`), and keeps the menu from depending on file formats.

**Alternatives rejected**

| Alternative | Why rejected |
|---|---|
| Client-server or microservices | There is no network, no second user and no deployment target; it would add complexity with no benefit |
| Single `main.c` with everything inside | Four people editing one file; no isolated testing; violates NFR-5 |
| Database for results | Out of scope in the SRS (no database); a flat file is sufficient for a short leaderboard |

**Key design decisions**

| ADR | Decision | Consequence |
|---|---|---|
| ADR-1 | Layered modules, one source/header pair per feature | Parallel work, per-module tests |
| ADR-2 | Flat text files for questions and results | No dependencies; file is human-readable; no integrity protection (see 3.9) |
| ADR-3 | Fixed, shared function signatures and structs | Modules can be built before their dependencies exist (stubs) |
| ADR-4 | Caller-owned fixed-size buffers, no dynamic allocation | No leaks or double-frees; the question limit is `MAX_QUESTIONS` (100) |
| ADR-5 | Every module prints its own screens; errors are one line starting `Error:` | Consistent UX (NFR-3); no logging framework needed |

### 3.6 Technology Stack and Data Stores

| Item | Choice |
|---|---|
| Language / standard | C, C99 |
| Compiler / build | GCC, `make` (`Makefile` builds `quiz`; `make test` runs the score tests) |
| Version control / CI | Git, GitHub; GitHub Actions workflow runs `make` on every push and pull request |
| Question bank | `data/questions.txt`: for each question, one line of text, four option lines, then one line with the correct letter A to D |
| Results store | `results.txt`: one `Name,Score` line per attempt, appended |
| Platforms | Windows, Linux, macOS terminals |

### 3.7 Risks and Mitigations

| Risk | Impact | Mitigation |
|---|---|---|
| Quiz Engine not ready when others integrate | Cannot demo end to end | Stubs with the agreed signatures are on `main`; scoring and storage are tested on their own |
| Question file malformed or missing | Quiz cannot start | `load_questions` returns an error; menu shows an error and continues (NFR-4) |
| Two people edit the same file | Merge conflicts | File ownership table in `TEAM-TASKS.md`; one pull request per issue, reviewed by the repo owner |
| `results.txt` edited or corrupted by hand | Wrong leaderboard | Reader skips malformed lines; documented as accepted residual risk (3.9) |
| Windows line endings (`\r\n`) in `results.txt` | Names ending in a stray `\r` | Reader strips `\r` before parsing |

### 3.8 Traceability to Requirements

| Requirement | Component | Function / location |
|---|---|---|
| REQ-1 Display menu | Menu Controller | `show_menu()` in `main.c` |
| REQ-2 Validate menu input | Menu Controller | `read_menu_choice()` |
| REQ-3 Re-prompt on invalid input | Menu Controller | main loop in `main()` |
| REQ-4 Navigate to feature | Menu Controller | `switch` in `main()`, `show_instructions()` |
| REQ-5 Return to menu | Menu Controller | `do ... while` loop in `main()` |
| REQ-6 Clean exit | Menu Controller | exit path of `main()` |
| REQ-7 Compare answer, update score | Scoring | `calculate_result()` |
| REQ-8 Count correct/incorrect | Scoring | `calculate_result()` |
| REQ-9 Total score and percentage | Scoring | `calculate_result()` |
| REQ-10 Pass/Fail at 40% | Scoring | `PASS_PERCENT` in `score.c` |
| REQ-11 Display result | Scoring | `show_result()` |
| REQ-12 Hand result to storage | Menu Controller, Storage | `save_result(name, &result)` call in `start_quiz()` |
| REQ-13 Save name and score | Storage | `save_result()` |
| REQ-14 Read stored results | Storage | `show_leaderboard()` (read step) |
| REQ-15 Sorted leaderboard | Storage | `show_leaderboard()` (sort step) |
| REQ-16 Missing file handled | Storage | `show_leaderboard()` |
| REQ-17 Load questions | Quiz Engine | `load_questions()` |
| REQ-18 One question at a time | Quiz Engine | `run_quiz()` |
| REQ-19 Validate answer | Quiz Engine | `run_quiz()` |
| REQ-20 Record answer | Quiz Engine | `run_quiz()` fills `answers[]` |
| REQ-21 Next question | Quiz Engine | `run_quiz()` |
| REQ-22 Continue until complete | Quiz Engine | `run_quiz()` |
| NFR-1 Performance | all | no heavy processing; input handled line by line |
| NFR-2 Security (SEC-1 to SEC-6) | all | see 3.9 |
| NFR-3 Usability | all | `Error:` prefix and re-prompt (4.5) |
| NFR-4 Reliability | all | error table in 4.4 |
| NFR-5 Maintainability | all | layering and file ownership (3.4, 3.5) |

### 3.9 Security Architecture

The system has no accounts, no network and no privileged operations. Its **trust boundaries** are (a) the keyboard, whose input is untrusted, and (b) the two local files, which any local user can edit.

**Threat model (STRIDE)**

| Threat | Scenario | Control | Requirement |
|---|---|---|---|
| Spoofing | Entering someone else's name | Not applicable: no authentication by design (single local user) | SRS 5.3 |
| Tampering | A name containing a comma or newline corrupts the results file or forges another record | Commas, `\r` and `\n` in the name are replaced by spaces before writing | SEC-2 |
| Tampering | Hand-editing `results.txt` | Accepted residual risk; reader skips malformed lines | SEC-4 |
| Repudiation | Denying a score | Not applicable for a local practice tool | |
| Information disclosure | Error text reveals paths or OS details | Fixed one-line messages only; no `perror`, no file names, no addresses | SEC-1 |
| Denial of service / crash | Very long input, empty input, EOF, missing or unreadable file | Bounded `fgets` buffers, overflow discarded, EOF detected, every file call checked | SEC-3, SEC-4, SEC-6 |
| Memory safety | Buffer overflow via name or menu line | Fixed buffers (64 bytes), length checked, `strtol` with end-pointer validation | SEC-3 |
| Elevation of privilege | Choosing an arbitrary file to read or write | File names are compile-time constants, never taken from input | SEC-5 |

**Security design rules for all modules**
1. Read keyboard input only with bounded functions (`fgets`); never `gets` or unbounded `scanf("%s")`.
2. Check the return value of every file operation and every `NULL` pointer argument.
3. Print only the fixed messages listed in 4.4.
4. Use constants for file names.

---

## 4. Design

### 4.1 Design Overview

`main()` runs a menu loop. Option 1 calls `start_quiz()`, which asks for a name, loads the questions, runs the quiz, calculates and shows the result, and saves it. Option 2 calls `show_leaderboard()`. Option 3 prints the instructions. Option 4 or end of input leaves the loop and exits.

**Shared data structures**

```c
typedef struct {            /* quiz.h */
    char text[256];
    char options[4][128];   /* A, B, C, D */
    char correct;           /* 'A'..'D' */
} Question;

typedef struct {            /* score.h */
    int score, correct, incorrect, total;
    double percent;
    int passed;             /* 1 = Pass, 0 = Fail */
} Result;
```

`score` equals `correct` (one mark per question), so `score + incorrect == total`. `main.c` holds the questions in a static array of `MAX_QUESTIONS` (100) and the answers in a `char` array, zero-filled so that unanswered questions never count as correct.

### 4.2 UML Sequence Diagrams

**Sequence 1: Start Quiz** (REQ-4, REQ-7 to REQ-13, REQ-17 to REQ-22)

![Sequence diagram: start quiz](diagrams/seq-take-quiz.png)

**Sequence 2: View Leaderboard** (REQ-14 to REQ-16)

![Sequence diagram: view leaderboard](diagrams/seq-leaderboard.png)

### 4.3 API Design

All interfaces are C functions declared in the headers. There are no network endpoints.

#### IQuiz (`include/quiz.h`, implemented in `src/quiz.c`)

| | `int load_questions(const char *path, Question qs[], int max)` |
|---|---|
| Purpose | Read up to `max` questions from the file at `path` into `qs` |
| Returns | Number of questions loaded (>= 1), or -1 on error |
| Errors | File cannot be opened or contains no valid question: returns -1 (the caller prints the message) |
| Notes | Every loaded question has exactly one correct letter A to D |

| | `void run_quiz(const Question qs[], int n, char answers[])` |
|---|---|
| Purpose | Present questions 0 to n-1 one at a time and store each answer |
| Postcondition | `answers[i]` is `'A'` to `'D'` for each answered question |
| Errors | Invalid choice: prints an `Error:` line and asks again; end of input: returns with the remaining answers untouched (caller pre-zeroes the array) |

#### IScore (`include/score.h`, implemented in `src/score.c`)

| | `Result calculate_result(const Question qs[], const char answers[], int n)` |
|---|---|
| Purpose | Mark the attempt |
| Returns | A `Result`: `score`, `correct`, `incorrect`, `total`, `percent = score / total * 100`, `passed = (percent >= 40.0)` |
| Errors | `qs` or `answers` is NULL, or `n <= 0`: returns an all-zero `Result` |

| | `void show_result(const Result *r)` |
|---|---|
| Purpose | Print score, percentage, correct and incorrect counts, and Pass/Fail |
| Errors | `r` is NULL: prints `Error: result is unavailable.` |

#### IStorage (`include/storage.h`, implemented in `src/storage.c`)

| | `int save_result(const char *name, const Result *r)` |
|---|---|
| Purpose | Append one `Name,Score` line to `results.txt` |
| Returns | 0 on success, -1 on any error |
| Errors | NULL argument, file cannot be opened or closed: returns -1 and prints nothing |
| Notes | Commas, `\r` and `\n` in `name` are replaced by spaces (SEC-2) |

| | `void show_leaderboard(void)` |
|---|---|
| Purpose | Read `results.txt` and print the entries sorted by score, highest first |
| Errors | File missing or unreadable: prints a short "no results yet" message and returns; malformed lines are skipped |

#### File formats

```
questions.txt   (repeated per question)
<question text>
<option A>
<option B>
<option C>
<option D>
<correct letter A-D>

results.txt     (one per attempt)
<name>,<score>
```

### 4.4 Error Handling, Logging and Monitoring

Errors are reported as a single line beginning `Error:` on the console, followed by a return to a safe state. No error message contains a file name, path or system error code (SEC-1).

| # | Condition | Detected by | Response | Requirement |
|---|---|---|---|---|
| E1 | Menu input is non-numeric, empty, has trailing text or is outside 1 to 4 | `read_menu_choice()` | `Error: please enter a number from 1 to 4.` then the menu again | REQ-3 |
| E2 | Menu line longer than the buffer | `read_menu_choice()` | Rest of the line discarded, same message as E1 | SEC-3 |
| E3 | End of input at the menu | `fgets` returns NULL | Goodbye message, clean exit | SEC-6 |
| E4 | Empty player name | `start_quiz()` | Name defaults to `Player` | NFR-3 |
| E5 | Question file missing, unreadable or empty | `load_questions()` returns <= 0 | `Error: could not load any questions.` and return to menu | NFR-4 |
| E6 | Invalid answer during the quiz | `run_quiz()` | `Error:` line and the same question again | REQ-19 |
| E7 | Scoring called with NULL or `n <= 0` | `calculate_result()` | Zeroed `Result`; `show_result(NULL)` prints `Error: result is unavailable.` | NFR-4 |
| E8 | Results file cannot be written | `save_result()` returns -1 | `Error: could not save your result.` and return to menu | SEC-4 |
| E9 | Results file missing at the leaderboard | `show_leaderboard()` | Short "no results yet" message and return to menu | REQ-16 |
| E10 | A line in `results.txt` is malformed | `show_leaderboard()` | Line skipped | SEC-4 |

**Logging.** A console quiz has no log file; adding one would create a second place where information could leak. Errors are visible on screen only.

**Monitoring and quality gates.** The GitHub Actions build runs on every push and pull request, and `make test` runs the unit tests for scoring. Both must pass before the repo owner merges a pull request.

### 4.5 UX Design

- One screen at a time; every screen ends with a prompt.
- Menus are numbered; quiz answers are single letters A to D.
- Every error starts with `Error:` and is followed by a new prompt.
- No colour or cursor control, so it works in any terminal.

**Main menu**

```
===== Online Quiz System =====
1. Start Quiz
2. View Leaderboard
3. Instructions
4. Exit
Enter your choice (1-4):
```

**Result screen**

```
===== Quiz Results =====
Score: 4/5
Percentage: 80.00%
Correct answers: 4
Incorrect answers: 1
Result: Pass
```

### 4.6 Open Issues and Next Steps

| # | Item | Plan |
|---|---|---|
| 1 | Quiz Engine (`load_questions`, `run_quiz`) is still a stub | Sprint-1, Sanjana (REQ-17 to REQ-22) |
| 2 | Leaderboard read and sort are not implemented | Sprint-2, Vaishnavi (REQ-14 to REQ-16) |
| 3 | REQ-12 says "score and percentage" are passed to storage, but the file stores name and score only (BR-4, Appendix B) | The whole `Result` is passed; only name and score are persisted. Keep BR-4 as the stored format |
| 4 | Question file format is defined by the sample file but not yet by a loader | Sanjana documents the format in her pull request |
| 5 | Ties on the leaderboard have no defined order | Keep file order for equal scores (stable sort) |
| 6 | Limit of 100 questions | Acceptable for the project; revisit only if the bank grows |

---

## 5. Appendices

### 5.1 Glossary
See SRS Appendix A. Additional terms: **Layered architecture** (modules grouped so that upper layers call lower layers only), **Stub** (a function with the final signature and no behaviour yet).

### 5.2 References
- IEEE 42010: Architecture description.
- IEEE 1016: Software design descriptions.
- Online Quiz System SRS v1.1 (`SRS.md`).
- OWASP: input validation guidance; CWE-120 (buffer overflow).

### 5.3 Tools
Mermaid (component and sequence diagrams), matplotlib (use case diagram), GCC, GNU Make, GitHub Actions.
