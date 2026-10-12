#include "score.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
  printf("=========================================\n");
  printf("        Testing score.c (REQ-11)        \n");
  printf("=========================================\n\n");

  /* Test 1: Standard quiz attempt (3 out of 5 correct -> 60%, Pass) */
  printf("--- Test Case 1: 3/5 Correct (60%%, Pass) ---\n");
  Question qs1[5] = {
      {"What is the capital of France?",
       {"Paris", "London", "Rome", "Berlin"},
       'A'},
      {"2 + 2 = ?", {"3", "4", "5", "6"}, 'B'},
      {"Which is a data type in C?", {"float", "banana", "car", "sky"}, 'A'},
      {"Which symbol denotes pointer?", {"*", "&", "%", "$"}, 'A'},
      {"Which function prints text?",
       {"scanf", "printf", "puts", "write"},
       'B'}};
  char answers1[5] = {
      'A', 'B', 'A', 'B',
      'A'}; /* Q1=A(ok), Q2=B(ok), Q3=A(ok), Q4=B(wrong), Q5=A(wrong) */

  Result r1 = calculate_result(qs1, answers1, 5);
  assert(r1.score == 3);
  assert(r1.correct == 3);
  assert(r1.incorrect == 2);
  assert(r1.total == 5);
  assert(r1.percent == 60.0);
  assert(r1.passed == 1);

  show_result(&r1);
  printf("--> Test 1 Passed!\n\n");

  /* Test Case 2: Failing score (1 out of 5 correct -> 20%, Fail) */
  printf("--- Test Case 2: 1/5 Correct (20%%, Fail) ---\n");
  char answers2[5] = {'A', 'C', 'C', 'C', 'C'}; /* Only Q1 is correct */
  Result r2 = calculate_result(qs1, answers2, 5);
  assert(r2.score == 1);
  assert(r2.correct == 1);
  assert(r2.incorrect == 4);
  assert(r2.total == 5);
  assert(r2.percent == 20.0);
  assert(r2.passed == 0);

  show_result(&r2);
  printf("--> Test 2 Passed!\n\n");

  /* Test Case 3: Perfect score (5 out of 5 correct -> 100%, Pass) */
  printf("--- Test Case 3: Perfect Score (100%%, Pass) ---\n");
  char answers3[5] = {'A', 'B', 'A', 'A', 'B'}; /* All correct */
  Result r3 = calculate_result(qs1, answers3, 5);
  assert(r3.score == 5);
  assert(r3.correct == 5);
  assert(r3.incorrect == 0);
  assert(r3.total == 5);
  assert(r3.percent == 100.0);
  assert(r3.passed == 1);

  show_result(&r3);
  printf("--> Test 3 Passed!\n\n");

  /* Test Case 4: Zero score (0 out of 5 correct -> 0%, Fail) */
  printf("--- Test Case 4: Zero Score (0%%, Fail) ---\n");
  char answers4[5] = {'C', 'C', 'C', 'C', 'C'}; /* None correct */
  Result r4 = calculate_result(qs1, answers4, 5);
  assert(r4.score == 0);
  assert(r4.correct == 0);
  assert(r4.incorrect == 5);
  assert(r4.total == 5);
  assert(r4.percent == 0.0);
  assert(r4.passed == 0);

  show_result(&r4);
  printf("--> Test 4 Passed!\n\n");

  /* Test Case 5: Null pointer handling (must not crash) */
  printf("--- Test Case 5: Safety Handling (NULL result) ---\n");
  show_result(NULL);
  printf("--> Test 5 Passed!\n\n");

  /* Test Case 6: Pass threshold boundary (4 of 10 correct -> 40%, Pass) */
  printf("--- Test Case 6: Boundary 4/10 (40%%, Pass) ---\n");
  Question qs10[10];
  char answers10[10];
  int i;
  for (i = 0; i < 10; i++) {
    qs10[i] = qs1[0];
    qs10[i].correct = 'A';
    answers10[i] = (i < 4) ? 'A' : 'B';
  }
  Result r6 = calculate_result(qs10, answers10, 10);
  assert(r6.score == 4);
  assert(r6.percent == 40.0);
  assert(r6.passed == 1);
  printf("--> Test 6 Passed!\n\n");

  /* Test Case 7: Just below the threshold (3 of 10 correct -> 30%, Fail) */
  printf("--- Test Case 7: Below boundary 3/10 (30%%, Fail) ---\n");
  answers10[3] = 'B';
  Result r7 = calculate_result(qs10, answers10, 10);
  assert(r7.score == 3);
  assert(r7.percent == 30.0);
  assert(r7.passed == 0);
  printf("--> Test 7 Passed!\n\n");

  /* Test Case 8: Invalid arguments must not crash (zero result) */
  printf("--- Test Case 8: Invalid arguments ---\n");
  Result r8 = calculate_result(NULL, answers10, 10);
  assert(r8.total == 0 && r8.score == 0 && r8.passed == 0);
  r8 = calculate_result(qs10, answers10, 0);
  assert(r8.total == 0 && r8.score == 0 && r8.passed == 0);
  printf("--> Test 8 Passed!\n\n");

  printf("=========================================\n");
  printf("   All test cases passed successfully!   \n");
  printf("=========================================\n");

  return 0;
}
