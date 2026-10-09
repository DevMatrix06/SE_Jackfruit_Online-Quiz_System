#ifndef SCORE_H
#define SCORE_H

#include "quiz.h"

/* score.h (Vikas) */
typedef struct {
    int score, correct, incorrect, total;
    double percent;
    int passed;                /* 1 = Pass, 0 = Fail */
} Result;
Result calculate_result(const Question qs[], const char answers[], int n);
void   show_result(const Result *r);

#endif
