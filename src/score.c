#include "score.h"

#include <stddef.h>
#include <stdio.h>

Result calculate_result(const Question qs[], const char answers[], int n)
{
Result r = {0, 0, 0, 0, 0.0, 0};
int i;


if (qs == NULL || answers == NULL || n <= 0)
    return r;

r.total = n;

for (i = 0; i < n; i++) {
    if (answers[i] == qs[i].correct) {
        r.score++;
        r.correct++;
    } else {
        r.incorrect++;
    }
}

r.percent = (double)r.score / r.total * 100.0;

/* Pass threshold: 40 percent, subject to the SRS. */
r.passed = (r.percent >= 40.0) ? 1 : 0;

return r;


}

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
