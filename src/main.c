#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quiz.h"
#include "score.h"
#include "storage.h"

#define MENU_MIN 1
#define MENU_MAX 4
#define MENU_EOF (-2)       /* returned when input ends (Ctrl+D / Ctrl+Z) */

#define QUESTIONS_FILE  "data/questions.txt"
#define MAX_QUESTIONS   100
#define PLAYER_NAME_LEN 64

/* Print the numbered main menu (REQ-1). */
static void show_menu(void)
{
    printf("\n===== Online Quiz System =====\n");
    printf("1. Start Quiz\n");
    printf("2. View Leaderboard\n");
    printf("3. Instructions\n");
    printf("4. Exit\n");
}

/* Read one line and accept it only if it is a single integer that is a
 * listed menu option (REQ-2). Returns the option, -1 if invalid, or
 * MENU_EOF if there is no more input. */
static int read_menu_choice(void)
{
    char line[64];
    char *end;
    long value;

    printf("Enter your choice (%d-%d): ", MENU_MIN, MENU_MAX);
    if (fgets(line, sizeof line, stdin) == NULL)
        return MENU_EOF;

    if (strchr(line, '\n') == NULL && !feof(stdin)) {   /* line too long */
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;                                           /* discard the rest */
        return -1;
    }

    value = strtol(line, &end, 10);
    if (end == line)                        /* no digits at all */
        return -1;
    while (*end == ' ' || *end == '\t' || *end == '\r')  /* trailing blanks */
        end++;
    if (*end != '\n' && *end != '\0')       /* extra characters */
        return -1;
    if (value < MENU_MIN || value > MENU_MAX)
        return -1;
    return (int)value;
}

/* Read a line into buf without the newline; discard any overflow.
 * Returns 0 on success, -1 if there is no more input. */
static int read_line(char *buf, size_t size)
{
    size_t len;

    if (fgets(buf, (int)size, stdin) == NULL)
        return -1;
    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[--len] = '\0';
    } else if (!feof(stdin)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    if (len > 0 && buf[len - 1] == '\r')
        buf[--len] = '\0';
    return 0;
}

/* Option 1: ask for a name, run the quiz, show and save the result (REQ-4). */
static void start_quiz(void)
{
    static Question qs[MAX_QUESTIONS];
    char answers[MAX_QUESTIONS];
    char name[PLAYER_NAME_LEN];
    Result result;
    int n;

    printf("Enter your name: ");
    if (read_line(name, sizeof name) != 0)
        return;
    if (name[0] == '\0')
        strcpy(name, "Player");

    n = load_questions(QUESTIONS_FILE, qs, MAX_QUESTIONS);
    if (n <= 0) {
        printf("Error: could not load any questions.\n");
        return;
    }

    run_quiz(qs, n, answers);
    result = calculate_result(qs, answers, n);
    show_result(&result);
    if (save_result(name, &result) != 0)
        printf("Error: could not save your result.\n");
}

/* Option 3: short instructions (REQ-4). */
static void show_instructions(void)
{
    printf("\n--- Instructions ---\n");
    printf("1. Choose 'Start Quiz' and enter your name.\n");
    printf("2. Each question has four options: A, B, C and D.\n");
    printf("3. Type the letter of your answer and press Enter.\n");
    printf("4. Your score is shown at the end and saved to the leaderboard.\n");
}

int main(void)
{
    int choice;

    /* Keep asking until the input is valid; never exit on bad input (REQ-3). */
    do {
        show_menu();
        choice = read_menu_choice();
        if (choice == MENU_EOF)
            break;                          /* stdin closed: nothing more to read */
        if (choice == -1)
            printf("Error: please enter a number from %d to %d.\n",
                   MENU_MIN, MENU_MAX);
    } while (choice == -1);

    /* Route to the selected feature (REQ-4). */
    switch (choice) {
    case 1: start_quiz();       break;
    case 2: show_leaderboard(); break;
    case 3: show_instructions(); break;
    default:                    break;      /* 4 = exit, or no more input */
    }
    return 0;
}
