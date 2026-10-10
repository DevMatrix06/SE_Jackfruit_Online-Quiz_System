#include <stdio.h>
#include "storage.h"

#define RESULTS_FILE "results.txt"

/* Appends "Name,Score" as one line to results.txt.
   Returns 0 on success, -1 on any error. */
int save_result(const char *name, const Result *r)
{
    FILE *fp;
    const char *p;

    if (name == NULL || r == NULL) {
        return -1;
    }

    fp = fopen(RESULTS_FILE, "a");      /* "a" = append, keeps old results */
    if (fp == NULL) {
        return -1;                       /* no paths or details printed */
    }

    /* Commas/newlines in a name would break the Name,Score format,
       so replace them with spaces. */
    for (p = name; *p != '\0'; p++) {
        fputc((*p == ',' || *p == '\n' || *p == '\r') ? ' ' : *p, fp);
    }
    fprintf(fp, ",%d\n", r->score);

    if (fclose(fp) != 0) {
        return -1;
    }
    return 0;
}

void show_leaderboard(void)
{
}