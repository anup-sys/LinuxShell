#ifndef JOBS_H
#define JOBS_H

#include <sys/types.h>

#define MAX_JOBS 100

typedef struct
{
    pid_t pid;
    char command[1024];
    int active;
} Job;

void add_job(pid_t pid, const char *command);
void list_jobs(void);
void remove_job(pid_t pid);

#endif