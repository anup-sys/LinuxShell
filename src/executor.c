#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "executor.h"
#include "background.h"
#include "redirection.h"
#include "pipes.h"
#include "jobs.h"

void execute_command(char **args)
{
    /* Handle pipe commands first */
    if (has_pipe(args))
    {
        execute_pipe(args);
        return;
    }

    /* Handle background commands */
    int background = is_background_command(args);

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        /* Handle input/output redirection */
        handle_redirection(args);

        execvp(args[0], args);

        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (background)
        {
            printf("[Background PID: %d]\n", pid);

            add_job(pid, args[0]);
        }
        else
        {
            waitpid(pid, NULL, 0);
        }
    }
}