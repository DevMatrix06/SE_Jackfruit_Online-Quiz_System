# Software Test Plan (STP): Online Quiz System

**Project:** Online Quiz System (console application in C)
**Version:** 1.0
**Authors:** Team Jackfruit (Tejas, Sanjana, Vikas, Vaishnavi)
**Date:** 12-10-2026
**Status:** Baseline; test cases designed, first execution results recorded against `main` (commit `2da664a`)

---

## 1. Introduction

**Purpose.** This document says how the Online Quiz System is tested: what is tested, how, with what, when and by whom. It also links every test case to the SRS requirement it checks.

**Scope.** All functional requirements REQ-1 to REQ-22 and all non-functional requirements NFR-1 to NFR-5, including the security requirements SEC-1 to SEC-6 of SRS v1.2. Testing is done on the compiled program and on single C modules.

**References.**
- Online Quiz System SRS v1.2 (`SRS.md`)
- Software Architecture and Design Specification v1.1 (`docs/SAD.md`)
- Mini-project deliverables, Part-1 and Part-2

**Definitions.**

| Term | Meaning |
|---|---|
| SRS | Software Requirements Specification |
| SAD | Software Architecture and Design specification |
| RTM | Requirements Traceability Matrix (Section 13) |
| TC | Test case |
| Blocked | Cannot be run yet because the code it needs is not merged |

---

## 2. Test Items

| Item | File(s) | Owner |
|---|---|---|
| Menu Controller | `src/main.c` | Tejas |
| Quiz Engine | `src/quiz.c`, `include/quiz.h`, `data/questions.txt` | Sanjana |
| Scoring Module | `src/score.c`, `include/score.h` | Vikas |
| Result Storage and Leaderboard | `src/storage.c`, `include/storage.h` | Vaishnavi |
| Build system and CI | `Makefile`, `.github/workflows/build.yml` | Tejas |
| Integrated program | `quiz` / `quiz.exe` | Team |

---

## 3. Features to be Tested

| SRS ID | Feature | Type |
|---|---|---|
| REQ-1 | Display numbered main menu | Functional |
| REQ-2 | Validate menu input | Functional |
| REQ-3 | Re-prompt on invalid input | Functional (negative) |
| REQ-4 | Navigate to the selected feature | Functional |
| REQ-5 | Return to main menu | Functional |
| REQ-6 | Clean exit | Functional |
| REQ-7 | Compare answer to correct option, update score | Functional |
| REQ-8 | Track correct and incorrect counts | Functional |
| REQ-9 | Calculate total score and percentage | Functional |
| REQ-10 | Pass/Fail at 40% | Functional |
| REQ-11 | Display score, percentage and counts | Functional |
| REQ-12 | Pass result to storage | Integration |
| REQ-13 | Save name and score to file | Functional |
| REQ-14 | Read stored results | Functional |
| REQ-15 | Leaderboard sorted descending | Functional |
| REQ-16 | Missing results file handled | Functional (negative) |
| REQ-17 to REQ-22 | Quiz engine: load, display, validate, record, proceed, complete | Functional |
| NFR-1 | Input processed within 1 second | Performance |
| NFR-2 (SEC-1 to SEC-6) | Security | Security |
| NFR-3 | Usability: clear prompts, `Error:` messages | Usability |
| NFR-4 | Reliability: no crash on bad input or missing files | Negative |
| NFR-5 | Maintainability: modular structure | Inspection |

---

## 4. Features Not to be Tested

| Item | Reason |
|---|---|
| User authentication, accounts, roles | Out of scope in the SRS (single local user) |
| Network, web, database, GUI | Not part of the product |
| Concurrent or multi-user use | SRS constraint: single user, single session |
| C standard library and operating system | Assumed to work correctly; not part of this project |
| Leaderboards with more than 100 stored results | More than NFR-1 expects |
| Other languages, screen-reader support | Not needed in this version |

---

## 5. Test Approach / Strategy

**Levels**

| Level | What | How |
|---|---|---|
| Unit | One module on its own (scoring, storage functions) | Small C programs using `assert`, e.g. `tests/test_score.c`, run with `make test` |
| Integration | Menu Controller working with the other modules (REQ-12: quiz, then score, then storage) | Run the real program with input sent from a script |
| System | The whole program checked against the SRS | Manual runs and scripted runs in the console |
| Acceptance | Demo videos (Sprint-1 1 min, Sprint-2 2 min) and instructor review | Walk-through of the working product |

**Types.** Functional, negative (wrong input and file errors), performance (timing), usability (inspection and walk-through), security (5.1), and regression (run the earlier tests again after each merge).

**Method.** Input is sent to the program from a script (`printf '1\nAsha\n...' | ./quiz`), so every run is the same. The output is compared with what the SRS says.

**Entry criteria**
- The code builds with `gcc -Wall -std=c99` without warnings.
- The GitHub Actions build is green for the commit under test.
- Test data (`data/questions.txt`, and a `results.txt` filled with sample data) is available.

**Exit criteria**
- 100% of planned test cases executed.
- Every test case passes, or each failure has a recorded defect with an owner and a decision.
- No open critical defect (crash, data loss, wrong score).
- All Sprint-1 and Sprint-2 requirements are covered by at least one passing test.

### 5.1 Security Validation

Security testing covers the six security requirements in SRS Section 5.3.2. The program has no network and no login, so the checks focus on input handling, file handling and not showing system details.

| Check | Method | Requirement | Test case |
|---|---|---|---|
| Error text shows no paths, system codes or addresses | Cause each error (missing question file, results file that cannot be written) and read the output | SEC-1 | TC-16 |
| A player name cannot damage or fake a record | Save names containing `,`, CR and LF; look at `results.txt` | SEC-2 | TC-09 |
| Very long and wrong input does not overflow or crash | Odd input: a 5000-character line, an empty line, letters instead of a number, extra text after a number | SEC-3 | TC-03, TC-17 |
| File problems do not crash the program | Make the results file impossible to open (a folder with the same name), remove it, leave it empty | SEC-4 | TC-14, TC-16 |
| File names cannot be chosen by the user | Code review: every `fopen` uses a name fixed in the code | SEC-5 | TC-18 |
| End of input is handled | End the input at the menu and at the name prompt | SEC-6 | TC-05 |
| Risky C functions are not used | Search the code (`grep`) for `gets`, `scanf`, `sprintf` and `strcpy` without a limit; compile with `-Wall` | SEC-3 | TC-18 |
| Memory errors | Run all the tests once more with `-fsanitize=address,undefined` before the code freeze | SEC-3 | Sprint-2 regression run |

---

## 6. Test Environment

| Item | Detail |
|---|---|
| Hardware | Standard Windows laptop or desktop; no special devices |
| Operating systems | Windows 11 (MinGW GCC, Git Bash / PowerShell); Ubuntu (GitHub Actions) |
| Compiler / build | GCC with `-Wall -std=c99`, GNU Make |
| Tools | Git, GitHub Actions, shell scripts to send input, `time` to measure speed, GitHub issues to track defects |
| Test data | `data/questions.txt` (5 questions); `results.txt` files filled with sample data for each test; a folder named `results.txt` for the write-failure case |
| Run directory | Repository root (the file paths in the program are relative) |

---

## 7. Test Schedule

| Milestone | Date | Notes |
|---|---|---|
| Test case design complete | 12-Oct-2026 | This document |
| Unit tests for scoring executed | 12-Oct-2026 | 8 cases, `make test` |
| Menu and negative tests executed | 12-Oct-2026 | Results in Section 13 |
| Sprint-1 integration run (menu, quiz, score, save) | 19 to 23 Oct 2026 | After Quiz Engine pull requests merge |
| Sprint-1 demo video | 23-Oct-2026 | Issue DEMO-1 |
| Run all test cases (TEST-1), and run the earlier tests again with memory checks | 26 to 30 Oct 2026 | Sprint-2 |
| Code freeze and final report | 30-Oct-2026 | Issue DEMO-2 |

---

## 8. Test Deliverables

- Test Plan (this document)
- Test cases and results (Section 13)
- Unit test source `tests/test_score.c` and the `make test` target
- Test data files and scripted inputs
- Defect reports (GitHub issues labelled with the requirement ID)
- Test summary report (Section 14, updated after each run)

---

## 9. Roles and Responsibilities

| Role | Name | Responsibility |
|---|---|---|
| QA Lead | Sanjana | Owns TEST-1: runs the full suite and logs results |
| Test Engineer (scoring) | Vikas | Maintains `tests/test_score.c`; unit and boundary tests |
| Test Engineer (storage, security) | Vaishnavi | Storage, leaderboard and security checks (5.1) |
| Developer / Product Owner / Repo Owner | Tejas | Menu tests, CI, review and merge, sign-off |

---

## 10. Risks and Mitigation

| Risk | Mitigation |
|---|---|
| Quiz Engine is late, so tests of the whole quiz are blocked | Test scoring and storage on their own; run the whole-quiz tests as soon as the engine is merged |
| Leaderboard (Sprint-2) leaves little time to test | Test cases are written now and the sample data is prepared in advance |
| Tests depend on the working directory | Always run from the repository root |
| Windows and Linux end lines differently in `results.txt` | Include a file with Windows (CRLF) line endings in the leaderboard tests |
| Manual tests are skipped when time is short | Scripts and `make test` keep the common checks to one command |

---

## 11. Assumptions and Dependencies

- The Quiz Engine uses the function names and arguments in `quiz.h` exactly.
- The question file follows the layout in SAD Section 3.6.
- `results.txt` is created by the program; tests start from a known state by deleting it or filling it with sample data.
- GitHub Actions and a local GCC are available throughout the testing period.

---

## 12. Suspension and Resumption Criteria

**Suspend** testing if the build on `main` fails, or more than 30% of the planned cases are blocked by a single defect.
**Resume** when the build is green again and the blocking defect is fixed and merged.

---

## 13. Test Case Management and Traceability

### 13.1 Test Cases

Result key: **Pass** and **Fail** are recorded results; **Blocked** needs code that is not merged yet; **Not run** is planned for a later sprint. Run on 12-Oct-2026 on `main` at commit `2da664a`, together with the 8 scoring unit tests in `tests/test_score.c`.

| TC | Requirement | Type | Steps | Expected result | Result |
|---|---|---|---|---|---|
| TC-01 | REQ-1 | Functional | Start the program | Menu shows 1 Start Quiz, 2 View Leaderboard, 3 Instructions, 4 Exit and the prompt `Enter your choice (1-4):` | **Pass** |
| TC-02 | REQ-2, REQ-4 | Functional | Enter `3` at the menu | Instructions screen is shown | **Pass** |
| TC-03 | REQ-3, NFR-4, SEC-3 | Negative | Enter `abc`, `0`, `5`, an empty line and `4 x` one after another | Each gives `Error: please enter a number from 1 to 4.` and the menu again; the program keeps running | **Pass** (5 errors, no exit) |
| TC-04 | REQ-5 | Functional | Enter `3`, then `4` | After the instructions the menu is displayed again before exit | **Pass** (menu shown twice) |
| TC-05 | REQ-6, SEC-6 | Functional / negative | (a) Enter `4`. (b) Run with empty standard input | Goodbye message and exit code 0 in both cases | **Pass** |
| TC-06 | REQ-7, REQ-8, REQ-9 | Unit | `calculate_result` with 5 questions: 3, 1, 5 and 0 correct | Scores 3, 1, 5, 0; correct + incorrect = total; percentages 60, 20, 100, 0 | **Pass** (Test 1 to 4) |
| TC-07 | REQ-10 | Unit (boundary) | 4 of 10 correct, then 3 of 10 correct | 40% is Pass; 30% is Fail | **Pass** (Test 6, 7) |
| TC-08 | REQ-11 | Unit | `show_result` with a result; then with NULL | Prints score, percentage, correct and incorrect counts and Pass/Fail; NULL prints `Error: result is unavailable.` and does not crash | **Pass** (Test 1 to 5) |
| TC-09 | REQ-13, SEC-2 | Functional / security | `save_result("Tara,Bad", ...)`, then names `A` and `Line` | Records are `Tara Bad,4`, `A,4`, `Line,4`; one line each, return 0 | **Pass** |
| TC-10 | REQ-12 | Integration | Complete a quiz as `Asha` | One new line `Asha,<score>` is appended to `results.txt` | **Blocked** (Quiz Engine) |
| TC-11 | REQ-17 to REQ-22 | System | Start quiz, answer every question | Questions appear one at a time with options A to D; each answer is recorded; the quiz ends after the last question and shows the result | **Blocked** (Quiz Engine) |
| TC-12 | REQ-19 | Negative | During a question enter `E`, an empty line, `1`, then `B` | Each invalid entry gives an `Error:` line and the same question again; `B` is accepted | **Blocked** (Quiz Engine) |
| TC-13 | REQ-14, REQ-15 | Functional | Fill `results.txt` with `Vikas,10`, `Vaishnavi,8`, `Tejas,9`; choose View Leaderboard | Order shown is 10, 9, 8 | **Not run** (Sprint-2) |
| TC-14 | REQ-16, SEC-4 | Negative | Delete `results.txt`; choose View Leaderboard | A short "no results yet" message and return to the menu; no crash | **Fail** (known): no crash, but the leaderboard is still a stub and prints nothing; due in Sprint-2 |
| TC-15 | NFR-1 | Performance | Time a full scripted run: menu, start quiz, name, exit | Each response within 1 second | **Pass** (whole run 0.07 s) |
| TC-16 | SEC-1, SEC-4 | Security | Make `results.txt` a folder; call `save_result` | Returns -1; the program prints only `Error: could not save your result.` with no path or system text | **Pass** (returns -1; message verified in `main.c`) |
| TC-17 | SEC-3, NFR-4 | Security / negative | Feed a 5000-character line at the menu, then `4` | One `Error:` message, rest of the line discarded, program continues and exits normally | **Pass** |
| TC-18 | SEC-5, SEC-3 | Security / inspection | Search the source for `fopen`, `gets`, `scanf`, `sprintf`, `strcpy` | `fopen` uses only the `RESULTS_FILE` constant; no `gets`, `scanf` or `sprintf`; the single `strcpy` copies the literal `"Player"` into a 64-byte buffer | **Pass** (re-check when `quiz.c` is merged) |
| TC-19 | NFR-5 | Inspection | Compile `score.c` with its test without the other modules | Builds and runs on its own | **Pass** (`make test`) |
| TC-20 | NFR-3 | Inspection | List every message printed on an error path | Each starts with `Error:` and is followed by a prompt or return to the menu | **Pass** (4 messages found) |

### 13.2 Requirements Traceability Matrix

| Requirement | Test case(s) |
|---|---|
| REQ-1 | TC-01 |
| REQ-2 | TC-02 |
| REQ-3 | TC-03 |
| REQ-4 | TC-02, TC-04 |
| REQ-5 | TC-04 |
| REQ-6 | TC-05 |
| REQ-7, REQ-8, REQ-9 | TC-06 |
| REQ-10 | TC-07 |
| REQ-11 | TC-08 |
| REQ-12 | TC-10 |
| REQ-13 | TC-09 |
| REQ-14, REQ-15 | TC-13 |
| REQ-16 | TC-14 |
| REQ-17 to REQ-22 | TC-11, TC-12 |
| NFR-1 | TC-15 |
| NFR-2: SEC-1 | TC-16 |
| NFR-2: SEC-2 | TC-09 |
| NFR-2: SEC-3 | TC-03, TC-17, TC-18 |
| NFR-2: SEC-4 | TC-14, TC-16 |
| NFR-2: SEC-5 | TC-18 |
| NFR-2: SEC-6 | TC-05 |
| NFR-3 | TC-20 |
| NFR-4 | TC-03, TC-17 |
| NFR-5 | TC-19 |

Every requirement in SRS v1.2 appears in at least one test case.

---

## 14. Test Metrics and Reporting

**Measures:** % of test cases run, % passed and failed, % of requirements covered by tests, open defects by severity, and how long defects stay open.

**Report after the first execution (12-Oct-2026):**

| Measure | Value |
|---|---|
| Test cases designed | 20 |
| Executed | 16 |
| Pass | 15 |
| Fail | 1 (TC-14, leaderboard not yet implemented) |
| Blocked | 3 (TC-10, TC-11, TC-12: Quiz Engine) |
| Not run | 1 (TC-13: Sprint-2) |
| Requirement coverage by test cases | 100% of REQ-1 to REQ-22 and NFR-1 to NFR-5 |
| Requirements checked by a passing test | REQ-1 to REQ-11, REQ-13, NFR-1, NFR-3, NFR-5, SEC-1 to SEC-3, SEC-5, SEC-6 |
| Unit test coverage of `score.c` | 100% of lines and 100% of branches (measured with `gcov`) |

Reports: a status update after each merged pull request that changes how the program behaves, and a final Test Summary Report at the code freeze.

---

## 15. Approvals

| Role | Name | Signature / Date |
|---|---|---|
| QA Lead | Sanjana | |
| Developer | Vikas / Vaishnavi | |
| Product Owner | Tejas | |
