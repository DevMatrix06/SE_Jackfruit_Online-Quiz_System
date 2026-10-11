#include <stdio.h>
#include <stddef.h>
#include "score.h"

/*
 * Calculate total score and percentage for completed quiz.
 * REQ-7: Compares each answer to the correct option and updates the score.
 * REQ-8: Counts correct and incorrect answers.
 * REQ-9: Calculates total score and percentage after questions are answered.
 * REQ-10: Classifies pass/fail based on a 40% threshold.
 */
Result calculate_result(const Question qs[], const char answers[], int n)
{
    Result r = {0, 0, 0, 0, 0.0, 0};
    int i;

    /* Validate inputs to prevent crashes on null pointers or non-positive count */
    if (qs == NULL || answers == NULL || n <= 0) {
        return r;
    }

    r.total = n;

    for (i = 0; i < n; i++) {
        if (answers[i] == qs[i].correct) {
            r.score++;
            r.correct++;
        } else {
            r.incorrect++;
        }
    }

    /* REQ-9: Percentage = (score / total) * 100 */
    if (r.total > 0) {
        r.percent = ((double)r.score / (double)r.total) * 100.0;
    }

    /* Pass threshold: 40% per SRS 4.3 */
    r.passed = (r.percent >= 40.0) ? 1 : 0;

    return r;
}

/*
 * Display the final score, percentage, and correct/incorrect counts (REQ-11).
 * Shows the result summary to the user immediately after the quiz ends.
 * Handles NULL safely to avoid crashing.
 */
void show_result(const Result *r)
{
    if (r == NULL) {
        printf("Error: result is unavailable.\n");
        return;
    }

    printf("\n===== Quiz Results =====\n");
    printf("Score: %d/%d\n", r->score, r->total);
    printf("Percentage: %.2f%%\n", r->percent);
    printf("Correct answers: %d\n", r->correct);
    printf("Incorrect answers: %d\n", r->incorrect);
    printf("Result: %s\n", r->passed ? "Pass" : "Fail");
}
