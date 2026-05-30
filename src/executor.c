#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "executor.h"
#include "background.h"
#include "redirection.h"

void execute_command(char **args)
{
    int background = is_background_command(args);

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        /* Handle > and < before execvp */
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
        }
        else
        {
            waitpid(pid, NULL, 0);
        }
    }
}