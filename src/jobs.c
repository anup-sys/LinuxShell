#include <stdio.h>
#include <string.h>

#include "jobs.h"

Job jobs[MAX_JOBS];

void add_job(pid_t pid, const char *command)
{
    for (int i = 0; i < MAX_JOBS; i++)
    {
        if (!jobs[i].active)
        {
            jobs[i].pid = pid;
            strcpy(jobs[i].command, command);
            jobs[i].active = 1;
            return;
        }
    }
}

void remove_job(pid_t pid)
{
    for (int i = 0; i < MAX_JOBS; i++)
    {
        if (jobs[i].active && jobs[i].pid == pid)
        {
            jobs[i].active = 0;
            return;
        }
    }
}

void list_jobs(void)
{
    for (int i = 0; i < MAX_JOBS; i++)
    {
        if (jobs[i].active)
        {
            printf("[%d] Running PID=%d %s\n",
                   i + 1,
                   jobs[i].pid,
                   jobs[i].command);
        }
    }
}