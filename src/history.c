#include <stdio.h>
#include <string.h>

#include "history.h"

#define MAX_HISTORY 100
#define MAX_CMD_LEN 1024

static char history[MAX_HISTORY][MAX_CMD_LEN];
static int history_count = 0;

void add_to_history(const char *command)
{
    if (history_count < MAX_HISTORY)
    {
        strcpy(history[history_count], command);
        history_count++;
    }
}

void show_history(void)
{
    for (int i = 0; i < history_count; i++)
    {
        printf("%d %s", i + 1, history[i]);
    }
}