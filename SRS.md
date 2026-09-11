# Software Requirements Specification
## Online Quiz System
Version 1.0

**Team:** Tejas, Sanjana, Vikas, Vaishnavi
**Project:** UE24CS341A – Software Engineering, Jackfruit Phase 1

---

## Revision History
<!-- Vaishnavi: fill in last, once all sections are merged -->

## Table of Contents
<!-- Vaishnavi: fill in last, once all sections are merged -->

---

## 1. Introduction
<!-- OWNER: Tejas -->

### 1.1 Purpose

### 1.2 Intended Audience

### 1.3 Product Scope

### 1.4 References

---

## 2. Overall Description
<!-- OWNER: Vikas -->

### 2.1 Product Perspective

### 2.2 Product Functions

### 2.3 User Classes and Characteristics

### 2.4 Operating Environment

### 2.5 Design and Implementation Constraints

### 2.6 Assumptions and Dependencies

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
#### Stimulus/Response Sequences
#### Functional Requirements

### 4.2 Quiz Engine (Question Delivery & Answer Capture)
<!-- OWNER: Sanjana -->
#### Description and Priority
#### Stimulus/Response Sequences
#### Functional Requirements

### 4.3 Scoring & Result Calculation
<!-- OWNER: Vikas -->
#### Description and Priority
#### Stimulus/Response Sequences
#### Functional Requirements

### 4.4 Result Storage & Leaderboard
<!-- OWNER: Vaishnavi -->
#### Description and Priority

The Result Storage & Leaderboard feature stores the player's name and final score after a quiz attempt. The system saves the result to a persistent file so that previously completed quiz attempts can be retrieved later. The stored results can be displayed as a leaderboard, with entries arranged from the highest score to the lowest score.

Priority: Medium

#### Stimulus/Response Sequences

1. The user completes the quiz.
2. The system calculates the final score.
3. The system saves the player's name and final score to the results file.
4. The user selects View Leaderboard from the main menu.
5. The system reads the previously stored results.
6. The system sorts the results according to score.
7. The system displays the leaderboard with the highest score first.
8. If no results have been stored yet, the system displays an appropriate message instead of crashing.

#### Functional Requirements

- **REQ-13:** The system shall save the player's name and final score to a persistent file after each quiz attempt.
- **REQ-14:** The system shall be able to read previously stored results from the results file.
- **REQ-15:** The system shall display stored results as a leaderboard, sorted by score in descending order.
- **REQ-16:** The system shall handle the case where no results file exists yet without crashing.
---

## 5. Other Nonfunctional Requirements
<!-- OWNER: Vaishnavi -->

### 5.1 Performance Requirements

The system shall display questions, menu options, and results without perceptible delay. User input shall be processed within one second under normal operating conditions on a standard computer.

The leaderboard shall be generated without significant delay for the expected number of stored quiz results.

### 5.2 Safety Requirements

Not applicable. The Online Quiz System is a non-safety-critical console application and does not control physical devices or processes that could cause safety hazards.

### 5.3 Security Requirements

The system does not require user authentication or login functionality. It is intended for single-user, local use.

The system shall avoid exposing unnecessary system or file information to the user during normal operation. If a result file cannot be accessed, the system shall display an appropriate error message rather than terminating unexpectedly.

### 5.4 Software Quality Attributes

Usability

The system shall provide clear menu options, prompts, and error messages so that a first-time user with basic computer knowledge can operate the quiz without difficulty.

Reliability

The system shall handle invalid user input and missing result files without crashing. The system shall continue operation or return to the appropriate menu whenever an input or file-related error can be handled.

Maintainability

The system shall be structured so that the question bank, result storage, and leaderboard functionality can be modified or extended without requiring major changes to unrelated system features.

### 5.5 Business Rules

BR-1: Only one quiz attempt shall be scored at a time.
BR-2: Each multiple-choice question shall have exactly one correct answer.
BR-3: Every completed quiz attempt shall produce a final score.
BR-4: Each stored result shall contain the player's name and final score.
BR-5: Leaderboard entries shall be displayed in descending order of score.

### 5.6 Other Requirements

Not applicable. No additional requirements have been identified beyond those specified in the preceding sections.

---

## Appendix A: Glossary
<!-- OWNER: Vaishnavi -->

**MCQ:**  
Multiple-Choice Question. A question that provides multiple answer options, with one correct option.

**REQ:**  
A unique identifier assigned to a functional requirement in the Software Requirements Specification.

**Question Bank:**  
The collection of multiple-choice questions available for the quiz.

**Quiz Engine:**  
The system feature responsible for presenting questions, accepting answers, and progressing through the quiz.

**Score:**  
The number of questions answered correctly by the player.

**Result:**  
The final outcome of a completed quiz attempt, including the player's score.

**Leaderboard:**  
A list of stored quiz results arranged according to the players' scores.

**Persistent File:**  
A file used to store information so that it remains available after the program terminates.
 
## Appendix B: Field Layouts
<!-- OWNER: Vaishnavi -->

Result File

The system shall use a persistent text file named results.txt to store completed quiz results.

Each record shall contain:

| Field | Description |
|---|---|
| Player Name | Name entered by the player |
| Score | Final score obtained in the quiz |

Example
Vaishnavi,8
Tejas,9
Sanjana,7
Vikas,10

Each line represents one completed quiz attempt.

## Appendix C: Requirement Traceability Matrix
<!-- OWNER: Vaishnavi -->
