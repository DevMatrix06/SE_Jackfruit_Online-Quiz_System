#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void run_quiz(const Question qs[], int n, char answers[])
{
    if (n <= 0) {
        printf("No questions available.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("\n----------------------------------------\n");
        printf("Question %d: %s\n", i + 1, qs[i].text);
        printf("A) %s\n", qs[i].options[0]);
        printf("B) %s\n", qs[i].options[1]);
        printf("C) %s\n", qs[i].options[2]);
        printf("D) %s\n", qs[i].options[3]);
        
        /* Note: Taking user input & storing answers will be completed in REQ-19 and REQ-20 */
        answers[i] = 'A'; /* Temporary placeholder */
    }
}