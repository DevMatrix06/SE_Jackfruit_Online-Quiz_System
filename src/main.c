#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quiz.h"
#include "score.h"
#include "storage.h"

#define MENU_MIN 1
#define MENU_MAX 4

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
 * listed menu option (REQ-2). Returns the option, or -1 if invalid. */
static int read_menu_choice(void)
{
    char line[64];
    char *end;
    long value;

    printf("Enter your choice (%d-%d): ", MENU_MIN, MENU_MAX);
    if (fgets(line, sizeof line, stdin) == NULL)
        return -1;

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

int main(void)
{
    int choice;

    show_menu();
    choice = read_menu_choice();
    if (choice == -1)
        printf("Invalid input.\n");
    else
        printf("You selected option %d.\n", choice);
    return 0;
}
