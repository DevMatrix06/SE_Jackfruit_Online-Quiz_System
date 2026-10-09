#include <stdio.h>
#include "quiz.h"
#include "score.h"
#include "storage.h"

/* Print the numbered main menu (REQ-1). */
static void show_menu(void)
{
    printf("\n===== Online Quiz System =====\n");
    printf("1. Start Quiz\n");
    printf("2. View Leaderboard\n");
    printf("3. Instructions\n");
    printf("4. Exit\n");
}

int main(void)
{
    show_menu();
    return 0;
}
