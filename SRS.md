# Software Requirements Specification
## Online Quiz System
Version 1.0

**Team:** Tejas, Sanjana, Vikas, Vaishnavi
**Project:** UE24CS341A – Software Engineering, Jackfruit Phase 1

---

## Revision History
<!-- Sanjana: fill in last, once all sections are merged -->

## Table of Contents

---

## 1. Introduction
<!-- OWNER: Tejas -->

### 1.1 Purpose
This document specifies the software requirements for the Online Quiz System, Version 1.0. The Online Quiz System is a console-based (command-line) application developed in C/C++ that presents users with multiple-choice questions and calculates their score based on the answers submitted. This SRS describes the functional and nonfunctional requirements of the system to guide its design, implementation, and testing.

### 1.2 Intended Audience and Reading Suggestions
This SRS is intended for: the development team (Tejas, Sanjana, Vikas, Vaishnavi), who use it as the shared specification for implementation and testing; the course faculty/evaluators, who use it to assess requirement quality and completeness for Jackfruit Phase 1; and team members acting as testers, who will derive their test cases directly from the functional requirements in Section 4. A reader unfamiliar with the project should read Section 2 (Overall Description) first, as it explains the product's scope and operating environment before the detailed feature requirements in Section 4 are introduced.

### 1.3 Product Scope
The Online Quiz System is a lightweight, offline, console-based quiz application that lets a user select and attempt a set of multiple-choice questions and receive an instant, automatically calculated score at the end. Its purpose is to replace manual, paper-based quizzes with a fast, self-contained digital alternative, and to demonstrate the team's understanding of core C/C++ programming concepts (control flow, functions, file handling) and the software engineering process, as required for the Level 3 mini-project (UE24CS341A). The scope of this version is intentionally kept small (Easy difficulty tier per the project problem statement): a single quiz taker per session, a fixed or file-based question bank, immediate scoring, and a simple leaderboard of past results. Features such as networked multiplayer quizzes, a graphical interface, a web/backend server, a database, or user accounts and login are explicitly out of scope for this phase.

### 1.4 References
- PES University, Dept. of CSE – "Jackfruit – Software Engineering Project Guidelines 2026" (UE24CS341A).
- Course-provided Synopsis/Problem Statement for the Online Quiz System (console-based, C/C++, Easy difficulty).
- Karl Wiegers – IEEE-style Software Requirements Specification template (structure followed by this document).
- cplusplus.com / cppreference.com – reference documentation for standard C/C++ library functions used for console I/O and file handling.

---

## 2. Overall Description
<!-- OWNER: Vikas -->

### 2.1 Product Perspective
The Online Quiz System is a new, self-contained, standalone console application; it is not a follow-on to an existing system and is not part of a larger product. It runs entirely on a single machine as one C/C++ executable, with no client-server split, no backend service, and no external database. The high-level flow is: User ↔ Console Program ↔ (optional) Local Question/Result Files. This is a mini-project for the Software Engineering course and is scoped accordingly — a small, offline, single-user tool.

### 2.2 Product Functions
At a high level, the system shall:
- Display a main menu and route the user to the feature they select.
- Present multiple-choice questions one at a time and capture the user's answer.
- Track correct/incorrect answers and compute a final score and percentage.
- Optionally save each attempt's result to a local file and display a leaderboard of past attempts.

Detailed requirements for each of these functions are given in Section 4 (System Features).

### 2.3 User Classes and Characteristics
This version of the system has a single user class:

| User Class | Privileges | Characteristics |
|---|---|---|
| Quiz Taker | Navigate the menu, attempt the quiz, view instructions, view the leaderboard/past results | Any user running the console program locally; no login or account is required; basic computer literacy assumed, no special technical expertise |

There is no separate administrator role, login system, or web-based interface in this version — the question bank is fixed or maintained directly by the team, not through an in-app admin panel.

### 2.4 Operating Environment
- **Client/runtime:** A terminal or console window (Windows Command Prompt/PowerShell, or a Linux/macOS terminal).
- **Language and compiler:** C/C++, compiled with a standard compiler such as GCC/g++ (or Turbo C++, if that is the toolchain specified by the course).
- **Storage:** No external database is used. If persistence is implemented (see Section 4.4), it uses simple local text files read and written via the standard C/C++ file I/O library.
- **Network:** None required — the application runs fully offline.

### 2.5 Design and Implementation Constraints
- The application must run entirely within a console/terminal — no graphical user interface (GUI) is in scope for this version.
- The system is single-user, single-session — no concurrent users and no multiplayer functionality.
- No web frontend, backend server, or database is used; any data persistence uses local flat files only.
- No login/authentication or administrator role is included in this version.
- The question bank size is limited and appropriate for a mini-project (a small, fixed or file-loaded set of multiple-choice questions).
- Git and GitHub are used for version control; individual commits are checked as evidence of each team member's contribution.

### 2.6 Assumptions and Dependencies
- The user has access to a working C/C++ compiler and a terminal to run the compiled program.
- The standard C/C++ library (console I/O, and file I/O if used) is available on the target machine — no third-party libraries are required.
- The question bank content is agreed upon and prepared by the team before implementation and is assumed to be well-formed (each question has exactly one correct option).
- The system depends on no external services, network connectivity, or runtime beyond the compiled executable itself.

---

## 3. External Interface Requirements
<!-- OWNER: Sanjana -->

### 3.1 User Interfaces

### 3.2 Software Interfaces

### 3.3 Communications Interfaces

### 3.4 Hardware Interfaces

### 3.5 Analysis Models

---

## 4. System Features

### 4.1 Main Menu & Navigation
<!-- OWNER: Tejas -->

#### Description and Priority
The Main Menu is the entry point of the Online Quiz System. On launch, it presents the user with a numbered list of available actions — starting the quiz, viewing instructions, viewing the leaderboard of past attempts, and exiting the program — and routes the user to the corresponding part of the system based on their input. Every other feature in this system is reached through this menu. **Priority: High.** Owned by Tejas.

#### Stimulus/Response Sequences
- User launches the program → the main menu is displayed with numbered options.
- User enters a valid menu option → the system navigates to the corresponding feature (Quiz Engine, Leaderboard view, Instructions, or Exit).
- User enters an invalid or non-numeric value → the system displays an error message and redisplays the menu without crashing.
- User selects the exit option → the system displays a closing message and terminates cleanly.
- User completes a quiz attempt or finishes viewing the leaderboard/instructions → the system returns control to the main menu automatically.

#### Functional Requirements

| ID | Requirement | Priority | Verification |
|----|-------------|----------|---------------|
| REQ-1 | The system shall display a numbered menu of available actions (Start Quiz, View Leaderboard, Instructions, Exit) immediately after the program starts. | High | Functional test |
| REQ-2 | The system shall accept a single integer as menu input and validate that it corresponds to one of the displayed options. | High | Functional test |
| REQ-3 | The system shall re-prompt the user with an error message if invalid (out-of-range or non-numeric) menu input is entered, without terminating the program. | High | Negative test |
| REQ-4 | The system shall navigate the user to the correct feature (Quiz Engine, Leaderboard, or Instructions screen) based on valid menu input. | High | Functional test |
| REQ-5 | The system shall return the user to the main menu after a selected feature (quiz attempt, leaderboard view, or instructions) has finished. | Medium | Functional test |
| REQ-6 | The system shall terminate the program cleanly, without residual open file handles, when the user selects the exit option. | Medium | Functional/code review |

---

### 4.2 Quiz Engine (Question Delivery & Answer Capture)
<!-- OWNER: Sanjana -->

#### Description and Priority
#### Stimulus/Response Sequences
#### Functional Requirements

---

### 4.3 Scoring & Result Calculation
<!-- OWNER: Vikas -->

#### Description and Priority
This feature tracks the user's correct and incorrect answers as the quiz progresses and, once the quiz is complete, calculates the final score, percentage, and an overall result classification (e.g. Pass/Fail or a grade band). **Priority: High.** Owned by Vikas.

#### Stimulus/Response Sequences
- Each answer submitted by the user (via the Quiz Engine, Section 4.2) → the system compares it to the correct option and updates the running score.
- The last question is answered → the system calculates the total score and percentage from the running tally.
- Score calculation completes → the system classifies the result (e.g. Pass/Fail) based on a defined threshold.
- Result classification completes → the system displays the final score, percentage, correct/incorrect counts, and result classification to the user.
- Result display completes → the final result data is handed off to the Result Storage & Leaderboard feature (Section 4.4) for persistence.

#### Functional Requirements

| ID | Requirement | Priority | Verification |
|----|-------------|----------|---------------|
| REQ-7 | The system shall compare each submitted answer to the question's correct option and update the running score accordingly. | High | Functional test |
| REQ-8 | The system shall separately track the count of correctly and incorrectly answered questions during the quiz. | High | Functional test |
| REQ-9 | The system shall calculate the total score and percentage once all questions in the quiz have been answered. | High | Functional test |
| REQ-10 | The system shall classify the overall result (e.g. Pass/Fail, or a grade band) based on a defined percentage threshold. | Medium | Functional test |
| REQ-11 | The system shall display the final score, percentage, and correct/incorrect counts to the user immediately after the quiz ends. | High | Functional test |
| REQ-12 | The system shall pass the completed result (score, percentage, timestamp) to the Result Storage & Leaderboard feature for persistence. | Medium | Integration test |

---

### 4.4 Result Storage & Leaderboard
<!-- OWNER: Vaishnavi -->

#### Description and Priority
#### Stimulus/Response Sequences
#### Functional Requirements

---

## 5. Other Nonfunctional Requirements
<!-- OWNER: Vaishnavi -->

### 5.1 Performance Requirements

### 5.2 Safety Requirements

### 5.3 Security Requirements

### 5.4 Software Quality Attributes

### 5.5 Business Rules

### 5.6 Other Requirements

---

## Appendix A: Glossary
<!-- OWNER: Vikas -->

## Appendix B: Field Layouts
<!-- OWNER: Vaishnavi -->

## Appendix C: Requirement Traceability Matrix
<!-- OWNER: Sanjana -->
