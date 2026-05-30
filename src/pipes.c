#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "pipes.h"

int has_pipe(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "|") == 0)
            return 1;
    }

    return 0;
}

void execute_pipe(char **args)
{
    int pipe_index = -1;

    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "|") == 0)
        {
            pipe_index = i;
            break;
        }
    }

    if (pipe_index == -1)
        return;

    args[pipe_index] = NULL;

    char **left = args;
    char **right = &args[pipe_index + 1];

    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return;
    }

    pid_t p1 = fork();

    if (p1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);

        close(fd[0]);
        close(fd[1]);

        execvp(left[0], left);

        perror("execvp");
        exit(EXIT_FAILURE);
    }

    pid_t p2 = fork();

    if (p2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);

        close(fd[1]);
        close(fd[0]);

        execvp(right[0], right);

        perror("execvp");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
}