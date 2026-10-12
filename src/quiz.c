#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "quiz.h"

int load_questions(const char *path, Question qs[], int max)
{
    FILE *fp = fopen(path, "r");
    if (!fp) {
        return -1;
    }

    int count = 0;
    char line[256];

    while (count < max && fgets(qs[count].text, sizeof(qs[count].text), fp)) {
        /* Strip newline characters */
        qs[count].text[strcspn(qs[count].text, "\r\n")] = '\0';

        /* Read all 4 options */
        for (int i = 0; i < 4; i++) {
            if (!fgets(qs[count].options[i], sizeof(qs[count].options[i]), fp)) {
                fclose(fp);
                return count;
            }
            qs[count].options[i][strcspn(qs[count].options[i], "\r\n")] = '\0';
        }

        /* Read the correct option letter ('A'..'D') */
        if (fgets(line, sizeof(line), fp)) {
            qs[count].correct = line[0];
        } else {
            fclose(fp);
            return count;
        }

        count++;
    }

    fclose(fp);
    return count;
}

#define ANSWER_LINE_LEN 64

/* Reads one line from the keyboard into buf. Extra characters on the line
   are discarded so the buffer cannot overflow (SEC-3).
   Returns 0 on success, -1 if there is no more input. */
static int read_answer_line(char *buf, size_t size)
{
    size_t len;
    int c;

    if (fgets(buf, (int)size, stdin) == NULL)
        return -1;
    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[--len] = '\0';
    } else if (!feof(stdin)) {
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    if (len > 0 && buf[len - 1] == '\r')
        buf[len - 1] = '\0';
    return 0;
}

/* Returns 'A'..'D' if the line is exactly one of those letters (either case,
   spaces around it allowed), otherwise 0. */
static char parse_answer(const char *s)
{
    char c;

    while (*s == ' ' || *s == '\t')
        s++;
    c = (char)toupper((unsigned char)*s);
    if (c < 'A' || c > 'D')
        return 0;
    s++;
    while (*s == ' ' || *s == '\t')
        s++;
    return (*s == '\0') ? c : 0;
}

/* Shows the questions one by one and records the answer to each
   (REQ-18 to REQ-22). If the input ends early, the quiz stops and the
   remaining answers stay 0 (unanswered). */
void run_quiz(const Question qs[], int n, char answers[])
{
    char line[ANSWER_LINE_LEN];
    char ans;
    int i, k;

    for (i = 0; i < n; i++) {
        printf("\nQuestion %d of %d\n%s\n", i + 1, n, qs[i].text);
        for (k = 0; k < 4; k++)
            printf("  %c) %s\n", 'A' + k, qs[i].options[k]);

        /* Keep asking until the answer is A, B, C or D (REQ-19). */
        ans = 0;
        while (ans == 0) {
            printf("Your answer (A-D): ");
            if (read_answer_line(line, sizeof line) != 0) {
                printf("\n");
                return;
            }
            ans = parse_answer(line);
            if (ans == 0)
                printf("Error: please enter A, B, C or D.\n");
        }
        answers[i] = ans;   /* record it, then show the next question (REQ-20, REQ-21) */
    }
}
