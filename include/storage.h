#ifndef STORAGE_H
#define STORAGE_H

#include "score.h"

/* storage.h (Vaishnavi) */
int  save_result(const char *name, const Result *r);   /* 0 ok, -1 error */
void show_leaderboard(void);                            /* reads results.txt, sorted high to low */

#endif
