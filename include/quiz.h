#ifndef QUIZ_H
#define QUIZ_H

/* quiz.h (Sanjana) */
typedef struct {
    char text[256];
    char options[4][128];
    char correct;              /* 'A'..'D' */
} Question;
int  load_questions(const char *path, Question qs[], int max);  /* returns count, -1 on error */
void run_quiz(const Question qs[], int n, char answers[]);      /* fills answers[i] with 'A'..'D' */

#endif
