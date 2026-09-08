# Software Requirements Specification
## Online Quiz System
Version 1.0

**Team:** Tejas, Sanjana, Vikas, Vaishnavi  
**Project:** UE24CS341A – Software Engineering, Jackfruit Phase 1

---

# 1. Introduction

## 1.1 Purpose

This document specifies the requirements for the administrator module of the Online Quiz System.

The administrator module allows authorized administrators to securely log in, create and manage quizzes, add and manage questions, configure quiz settings, publish or unpublish quizzes, and monitor participant results.

The requirements defined in this section provide the basis for designing, implementing and testing the administrator functionality.

## 1.2 Intended Audience

This section is intended for the project development team, course faculty, testers and administrators of the Online Quiz System.

Developers will use these requirements during implementation, while testers will use them to prepare test cases for administrator functionality.

## 1.3 Product Scope

The administrator module provides authorized users with tools to manage the content and operation of the Online Quiz System.

An administrator can create quizzes, define quiz details, add questions and answer options, set correct answers and marks, configure quiz duration, publish or disable quizzes, and view participant performance.

The module ensures that only authorized administrators can perform these operations.

## 1.4 References

1. PES University, Department of Computer Science and Engineering – Jackfruit Phase-1 Software Engineering Project Guidelines 2026 (UE24CS341A).
2. PES University – Software Engineering project submission guidelines and reference SRS.
3. IEEE-style Software Requirements Specification structure used for the project.

---

# 2. Overall Description

## 2.1 Product Perspective

The administrator module is a part of the Online Quiz System web application.

It provides a separate administrative interface through which authorized administrators can manage quizzes and questions and monitor participant performance.

The high-level interaction is:

```text
Administrator → Admin Interface → Backend API → Database
````

The backend validates the administrator's identity and permissions before performing administrative operations.

## 2.2 Product Functions

The administrator module shall provide the following functions:

1. Administrator login.
2. Administrator authentication.
3. Administrator authorization.
4. Administrator dashboard.
5. Create quiz.
6. Edit quiz details.
7. Delete quiz.
8. Add questions.
9. Edit questions.
10. Delete questions.
11. Add answer options.
12. Define correct answers.
13. Assign marks to questions.
14. Set quiz duration.
15. Set quiz category and difficulty.
16. Publish a quiz.
17. Unpublish or disable a quiz.
18. View quiz attempts.
19. View participant scores.
20. View participant results.
21. View leaderboard information.
22. Logout from the administrator account.

## 2.3 User Classes and Characteristics

| User Class      | Privileges                                                            | Characteristics                                             |
| --------------- | --------------------------------------------------------------------- | ----------------------------------------------------------- |
| Administrator   | Manage quizzes, questions, quiz settings and view participant results | Authorized user responsible for maintaining the quiz system |
| Registered User | Attempt published quizzes and view own results                        | Normal quiz participant                                     |
| Guest User      | Access public pages such as home, registration and login              | Unauthenticated user                                        |

## 2.4 Operating Environment

1. Client: Modern web browsers such as Chrome, Firefox and Edge.
2. Frontend: Web-based administrator dashboard.
3. Backend: Server-side application providing authentication and administrative APIs.
4. Database: Database used to store administrator, quiz, question and result information.
5. Operating System: Windows, Linux or macOS.
6. Network: Internet or local network connection.

## 2.5 Design and Implementation Constraints

1. Administrator functions shall require authentication.
2. Administrator operations shall use role-based authorization.
3. Only authorized administrators shall be allowed to modify quiz content.
4. Passwords shall not be stored in plaintext.
5. Quiz and question data shall be stored persistently.
6. Git and GitHub shall be used for version control.
7. Agile development practices shall be followed.
8. The administrator shall not be able to directly modify participant scores through the quiz interface.

## 2.6 Assumptions and Dependencies

1. An administrator account is created before administrator functions are used.
2. The administrator has valid login credentials.
3. The backend server and database are available.
4. The administrator has a stable network connection.
5. Quiz information entered by the administrator is valid.
6. The system depends on the selected frontend, backend and database technologies.

---

# 3. External Interface Requirements

## 3.1 User Interfaces

### Administrator Login

The administrator login interface shall provide:

* Username or email field.
* Password field.
* Login button.
* Error messages for invalid credentials.

### Administrator Dashboard

The administrator dashboard shall provide access to:

* Quiz management.
* Question management.
* Published quizzes.
* Draft/unpublished quizzes.
* Participant results.
* Leaderboard.
* Logout.

### Quiz Management Interface

The administrator shall be able to:

* Create a new quiz.
* Edit quiz details.
* Delete a quiz.
* Set category.
* Set difficulty level.
* Set quiz duration.
* Publish a quiz.
* Unpublish or disable a quiz.

### Question Management Interface

The administrator shall be able to:

* Add questions.
* Edit questions.
* Delete questions.
* Add answer options.
* Define the correct answer.
* Set marks for a question.

### Result Management Interface

The administrator shall be able to view:

* Quiz name.
* Participant name.
* Score.
* Percentage.
* Number of correct answers.
* Number of incorrect answers.
* Submission time.
* Ranking information.

## 3.2 Software Interfaces

1. The administrator frontend shall communicate with the backend using HTTP/HTTPS APIs.
2. The backend shall communicate with the database to store and retrieve administrator, quiz, question and result data.
3. The authentication system shall verify administrator credentials.
4. The authorization system shall verify administrator privileges before protected operations.
5. API requests and responses shall use a structured format such as JSON.

## 3.3 Communications Interfaces

1. Client-server communication shall use HTTP/HTTPS.
2. JSON shall be used for API requests and responses.
3. Authentication information shall be transmitted using secure mechanisms.
4. HTTPS shall be used in production environments.
5. The system shall return suitable error responses when administrative requests fail.

## 3.4 Hardware Interfaces

No dedicated hardware is required for the administrator module.

The administrator may access the system using:

* Desktop computers.
* Laptops.
* Tablets.
* Mobile devices with supported web browsers.

## 3.5 Analysis Models

### Administrator Use Case Model

The main administrator use cases are:

```text
                    +-------------------------+
                    |   Online Quiz System    |
                    +-------------------------+
                              |
                        Administrator
                              |
            +-----------------+-----------------+
            |                 |                 |
          Login         Manage Quizzes      View Results
                              |
                       +------+------+
                       |             |
                 Manage Quiz   Manage Questions
                       |             |
                 Publish Quiz    Add Question
                 Edit Quiz       Edit Question
                 Delete Quiz     Delete Question
```

### Administrator Use Cases

| Use Case ID | Use Case                 | Primary Actor | Precondition             | Outcome                             |
| ----------- | ------------------------ | ------------- | ------------------------ | ----------------------------------- |
| UC-A01      | Administrator Login      | Administrator | Admin account exists     | Authenticated admin session         |
| UC-A02      | Create Quiz              | Administrator | Admin is authenticated   | New quiz is created                 |
| UC-A03      | Edit Quiz                | Administrator | Quiz exists              | Quiz details are updated            |
| UC-A04      | Delete Quiz              | Administrator | Quiz exists              | Quiz is deleted                     |
| UC-A05      | Add Question             | Administrator | Quiz exists              | Question is added                   |
| UC-A06      | Edit Question            | Administrator | Question exists          | Question is updated                 |
| UC-A07      | Delete Question          | Administrator | Question exists          | Question is deleted                 |
| UC-A08      | Publish Quiz             | Administrator | Quiz is valid            | Quiz becomes available to users     |
| UC-A09      | Unpublish Quiz           | Administrator | Quiz is published        | Quiz is removed from active quizzes |
| UC-A10      | View Participant Results | Administrator | Completed attempts exist | Participant results are displayed   |
| UC-A11      | View Leaderboard         | Administrator | Completed attempts exist | Leaderboard is displayed            |
| UC-A12      | Logout                   | Administrator | Admin is authenticated   | Admin session is terminated         |

---

# 4. System Features

## 4.1 Main Menu & Navigation

### Description and Priority

This feature provides the administrator with access to the major administrative functions through a centralized dashboard.

**Priority: High**

### Stimulus/Response Sequences

1. Administrator logs in → system verifies credentials.
2. Successful login → system displays the administrator dashboard.
3. Administrator selects a management option → system opens the selected management page.
4. Administrator logs out → system terminates the administrator session.

### Functional Requirements

| ID      | Requirement                                                                              | Priority | Verification    |
| ------- | ---------------------------------------------------------------------------------------- | -------- | --------------- |
| FR-A001 | The system shall allow an administrator to log in using valid administrator credentials. | High     | Functional test |
| FR-A002 | The system shall display the administrator dashboard after successful login.             | High     | Functional test |
| FR-A003 | The system shall provide navigation to quiz, question and result management sections.    | High     | Functional test |
| FR-A004 | The system shall prevent unauthenticated users from accessing administrator pages.       | High     | Security test   |
| FR-A005 | The system shall allow an administrator to log out securely.                             | High     | Functional test |

## 4.2 Quiz Management

### Description and Priority

This feature allows administrators to create and manage quizzes before making them available to users.

**Priority: High**

### Stimulus/Response Sequences

1. Administrator selects Create Quiz → system displays the quiz form.
2. Administrator enters quiz details → system validates the input.
3. System stores the quiz information.
4. Administrator can edit or delete the quiz.
5. Administrator can publish or unpublish the quiz.

### Functional Requirements

| ID      | Requirement                                                                   | Priority | Verification    |
| ------- | ----------------------------------------------------------------------------- | -------- | --------------- |
| FR-A006 | The system shall allow an administrator to create a quiz with a unique title. | High     | Functional test |
| FR-A007 | The system shall allow an administrator to enter a quiz description.          | Medium   | Functional test |
| FR-A008 | The system shall allow an administrator to set the quiz category.             | Medium   | Functional test |
| FR-A009 | The system shall allow an administrator to set the quiz difficulty.           | Medium   | Functional test |
| FR-A010 | The system shall allow an administrator to set the quiz duration.             | High     | Functional test |
| FR-A011 | The system shall allow an administrator to edit an existing quiz.             | High     | Functional test |
| FR-A012 | The system shall allow an administrator to delete an existing quiz.           | High     | Functional test |
| FR-A013 | The system shall allow an administrator to publish a valid quiz.              | High     | Functional test |
| FR-A014 | The system shall allow an administrator to unpublish a published quiz.        | Medium   | Functional test |
| FR-A015 | The system shall prevent an invalid quiz from being published.                | High     | Negative test   |

## 4.3 Question Management

### Description and Priority

This feature allows administrators to create and maintain the questions and answer options associated with a quiz.

**Priority: High**

### Stimulus/Response Sequences

1. Administrator selects a quiz.
2. Administrator selects Add Question.
3. Administrator enters the question and options.
4. Administrator selects the correct answer and marks.
5. System validates and stores the question.
6. Administrator can edit or delete the question later.

### Functional Requirements

| ID      | Requirement                                                                    | Priority | Verification     |
| ------- | ------------------------------------------------------------------------------ | -------- | ---------------- |
| FR-A016 | The system shall allow an administrator to add a question to an existing quiz. | High     | Functional test  |
| FR-A017 | The system shall allow an administrator to add answer options for a question.  | High     | Functional test  |
| FR-A018 | The system shall allow an administrator to define the correct answer.          | High     | Functional test  |
| FR-A019 | The system shall allow an administrator to assign marks to a question.         | High     | Functional test  |
| FR-A020 | The system shall allow an administrator to edit an existing question.          | High     | Functional test  |
| FR-A021 | The system shall allow an administrator to delete an existing question.        | High     | Functional test  |
| FR-A022 | The system shall validate all mandatory question fields before saving.         | High     | Negative test    |
| FR-A023 | The system shall associate each question with its selected quiz.               | High     | Integration test |
| FR-A024 | The system shall prevent unauthorized users from modifying questions.          | High     | Security test    |

## 4.4 Quiz Publishing and Availability

### Description and Priority

This feature controls whether a quiz is available for users to attempt.

**Priority: High**

### Stimulus/Response Sequences

1. Administrator creates and configures a quiz.
2. System checks whether required information is available.
3. Administrator selects Publish.
4. System changes the quiz status to Published.
5. The quiz becomes available to authorized users.
6. Administrator may later unpublish the quiz.

### Functional Requirements

| ID      | Requirement                                                                                           | Priority | Verification             |
| ------- | ----------------------------------------------------------------------------------------------------- | -------- | ------------------------ |
| FR-A025 | The system shall maintain a publication status for each quiz.                                         | High     | Database/functional test |
| FR-A026 | The system shall make a published quiz available to registered users.                                 | High     | Integration test         |
| FR-A027 | The system shall prevent an unpublished quiz from appearing in the active quiz list for normal users. | High     | Security test            |
| FR-A028 | The system shall allow an administrator to unpublish a previously published quiz.                     | High     | Functional test          |
| FR-A029 | The system shall preserve the questions and configuration when a quiz is unpublished.                 | Medium   | Persistence test         |

## 4.5 Result & Leaderboard Monitoring

### Description and Priority

This feature allows administrators to monitor participant performance by viewing completed quiz attempts, scores and leaderboard information.

**Priority: Medium**

### Stimulus/Response Sequences

1. User completes a quiz → system stores the result.
2. Administrator opens the Results section → system retrieves completed attempts.
3. Administrator selects a quiz → system displays its participant results.
4. Administrator opens the leaderboard → system displays rankings.

### Functional Requirements

| ID      | Requirement                                                                                                                     | Priority | Verification    |
| ------- | ------------------------------------------------------------------------------------------------------------------------------- | -------- | --------------- |
| FR-A030 | The system shall allow an authenticated administrator to view completed quiz attempts.                                          | High     | Functional test |
| FR-A031 | The system shall display the participant associated with each completed attempt.                                                | High     | Functional test |
| FR-A032 | The system shall display the score and percentage of each completed attempt.                                                    | High     | Functional test |
| FR-A033 | The system shall display the submission time of completed attempts.                                                             | Medium   | Functional test |
| FR-A034 | The system shall allow an administrator to view leaderboard information for a quiz.                                             | Medium   | Functional test |
| FR-A035 | The system shall prevent an administrator from directly modifying a calculated participant score through the results interface. | High     | Security test   |

---

# 5. Other Nonfunctional Requirements

## 5.1 Performance Requirements

| ID       | Category    | Measurable Requirement                                                                               | Verification     |
| -------- | ----------- | ---------------------------------------------------------------------------------------------------- | ---------------- |
| NFR-A001 | Performance | 95% of administrator dashboard requests shall complete within 2 seconds under the defined test load. | Performance test |
| NFR-A002 | Performance | Quiz creation and update requests shall complete within 2 seconds under the defined test load.       | Performance test |
| NFR-A003 | Performance | Question management requests shall complete within 2 seconds under the defined test load.            | Performance test |
| NFR-A004 | Performance | Participant result queries shall complete within 2 seconds under the defined test load.              | Performance test |

## 5.2 Safety Requirements

The administrator module does not directly control physical devices, so conventional physical safety requirements do not apply.

The system shall protect administrative data by:

1. Validating quiz and question information before storage.
2. Preventing unauthorized deletion or modification.
3. Preserving successfully stored quiz and question data.

## 5.3 Security Requirements

| ID       | Security Requirement                                                     | Validation Approach |
| -------- | ------------------------------------------------------------------------ | ------------------- |
| SEC-A001 | Administrator functions shall require authentication.                    | Security test       |
| SEC-A002 | Administrator passwords shall not be stored in plaintext.                | Code review         |
| SEC-A003 | Only administrators shall be allowed to create or modify quizzes.        | Authorization test  |
| SEC-A004 | Only administrators shall be allowed to add, edit or delete questions.   | Authorization test  |
| SEC-A005 | Unauthenticated users shall be denied access to administrator endpoints. | Security test       |
| SEC-A006 | Invalid or expired authentication credentials shall be rejected.         | Security test       |
| SEC-A007 | Normal users shall not be allowed to modify correct answers.             | Authorization test  |
| SEC-A008 | Normal users shall not be allowed to modify stored results.              | Authorization test  |

## 5.4 Software Quality Attributes

1. **Maintainability** – Administrative functions shall be divided into manageable modules.
2. **Reliability** – Successfully stored quiz and question data shall remain available.
3. **Usability** – The administrator dashboard shall provide clear navigation and understandable controls.
4. **Testability** – Quiz and question management operations shall be independently testable.
5. **Scalability** – The system shall support increasing numbers of quizzes, questions and participants.
6. **Security** – Administrator functions shall remain inaccessible to unauthorized users.

## 5.5 Business Rules

1. Only authenticated administrators may create quizzes.
2. Only administrators may modify or delete quizzes.
3. Only administrators may add, edit or delete questions.
4. A quiz must contain all required information before it can be published.
5. Every supported multiple-choice question must have a correct answer.
6. Unpublished quizzes shall not be available to normal users.
7. Administrators may view participant results but shall not directly modify automatically calculated scores.
8. Administrative operations shall follow role-based access control.
9. A published quiz shall use the question and settings configured by the administrator.

## 5.6 Other Requirements

1. Quiz and question information created by administrators shall be stored persistently.
2. The administrator interface shall use English in Version 1.0.
3. The design shall allow future addition of new question types.
4. The administrator interface shall work on supported desktop and mobile browsers.
5. Open-source libraries may be used where they satisfy the project requirements.

---

# Appendix A: Glossary

| Term           | Definition                                                                    |
| -------------- | ----------------------------------------------------------------------------- |
| Administrator  | Authorized user responsible for managing the quiz system.                     |
| Dashboard      | Main interface through which the administrator accesses management functions. |
| Quiz           | Collection of questions presented to users.                                   |
| Question       | Individual item included in a quiz.                                           |
| Answer Option  | Possible answer provided for a question.                                      |
| Correct Answer | Answer configured by the administrator as correct.                            |
| Publish        | Making a quiz available to users.                                             |
| Unpublish      | Removing a quiz from active availability.                                     |
| Draft          | Quiz that is still being prepared.                                            |
| Authentication | Process of verifying the administrator's identity.                            |
| Authorization  | Process of checking whether a user has permission to perform an action.       |
| Leaderboard    | Ranked list of participants based on quiz performance.                        |
| RBAC           | Role-Based Access Control used to restrict access according to user role.     |

---

# Appendix B: Field Layouts

## Administrator

| Field         | Length | Data Type       | Description                     | Mandatory |
| ------------- | -----: | --------------- | ------------------------------- | --------- |
| admin_id      |     24 | String/ObjectId | Unique administrator identifier | Y         |
| username      |     50 | String          | Administrator username          | Y         |
| email         |    100 | String          | Administrator email             | Y         |
| password_hash |    255 | String          | Secure password hash            | Y         |
| role          |     20 | Enum            | Administrator role              | Y         |
| created_at    |      – | DateTime        | Account creation time           | Y         |

## Quiz

| Field            | Length | Data Type       | Description                        | Mandatory |
| ---------------- | -----: | --------------- | ---------------------------------- | --------- |
| quiz_id          |     24 | String/ObjectId | Unique quiz identifier             | Y         |
| title            |    100 | String          | Quiz title                         | Y         |
| description      |    500 | String          | Quiz description                   | N         |
| category         |     50 | String          | Quiz category                      | Y         |
| difficulty       |     20 | Enum            | Quiz difficulty                    | N         |
| duration_minutes |      5 | Integer         | Quiz duration                      | Y         |
| status           |     20 | Enum            | Draft/Published/Unpublished        | Y         |
| created_by       |     24 | String/ObjectId | Administrator who created the quiz | Y         |
| created_at       |      – | DateTime        | Quiz creation date                 | Y         |

## Question

| Field          | Length | Data Type       | Description                | Mandatory |
| -------------- | -----: | --------------- | -------------------------- | --------- |
| question_id    |     24 | String/ObjectId | Unique question identifier | Y         |
| quiz_id        |     24 | String/ObjectId | Associated quiz            | Y         |
| question_text  |   1000 | String          | Question statement         | Y         |
| option_a       |    500 | String          | First answer option        | Y         |
| option_b       |    500 | String          | Second answer option       | Y         |
| option_c       |    500 | String          | Third answer option        | Y         |
| option_d       |    500 | String          | Fourth answer option       | Y         |
| correct_option |      1 | String/Enum     | Correct answer option      | Y         |
| marks          |      5 | Integer         | Marks assigned to question | Y         |

---

# Appendix C: Requirement Traceability Matrix

| Sl. No. | Requirement ID | Brief Description                   | Architecture Ref | Design Ref | Code File Ref | Test Case ID | System Test Case ID |
| ------: | -------------- | ----------------------------------- | ---------------- | ---------- | ------------- | ------------ | ------------------- |
|       1 | FR-A001        | Administrator login                 | TBD              | TBD        | TBD           | TBD          | TBD                 |
|       2 | FR-A006        | Create quiz                         | TBD              | TBD        | TBD           | TBD          | TBD                 |
|       3 | FR-A011        | Edit quiz                           | TBD              | TBD        | TBD           | TBD          | TBD                 |
|       4 | FR-A012        | Delete quiz                         | TBD              | TBD        | TBD           | TBD          | TBD                 |
|       5 | FR-A016        | Add question                        | TBD              | TBD        | TBD           | TBD          | TBD                 |
|       6 | FR-A020        | Edit question                       | TBD              | TBD        | TBD           | TBD          | TBD                 |
|       7 | FR-A021        | Delete question                     | TBD              | TBD        | TBD           | TBD          | TBD                 |
|       8 | FR-A013        | Publish quiz                        | TBD              | TBD        | TBD           | TBD          | TBD                 |
|       9 | FR-A030        | View participant attempts           | TBD              | TBD        | TBD           | TBD          | TBD                 |
|      10 | FR-A032        | View participant scores             | TBD              | TBD        | TBD           | TBD          | TBD                 |
|      11 | FR-A034        | View leaderboard                    | TBD              | TBD        | TBD           | TBD          | TBD                 |
|      12 | SEC-A003       | Quiz management authorization       | TBD              | TBD        | TBD           | TBD          | TBD                 |
|      13 | SEC-A004       | Question management authorization   | TBD              | TBD        | TBD           | TBD          | TBD                 |
|      14 | SEC-A008       | Protect stored results              | TBD              | TBD        | TBD           | TBD          | TBD                 |
|      15 | NFR-A001       | Administrator dashboard performance | TBD              | TBD        | TBD           | TBD          | TBD                 |

---

## Admin Requirement Summary

| Category                 | Count |
| ------------------------ | ----: |
| Functional Requirements  |    35 |
| Security Requirements    |     8 |
| Performance Requirements |     4 |
| Use Cases                |    12 |

```


