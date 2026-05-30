#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"
#include "history.h"
#include "jobs.h"

int handle_builtin(char **args)
{
    if (args[0] == NULL)
        return 1;

    /* exit */
    if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }

    /* cd */
    if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "cd: missing argument\n");
        }
        else
        {
            if (chdir(args[1]) != 0)
                perror("cd");
        }

        return 1;
    }

    /* pwd */
    if (strcmp(args[0], "pwd") == 0)
    {
        char cwd[1024];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf("%s\n", cwd);
        else
            perror("pwd");

        return 1;
    }

    /* history */
    if (strcmp(args[0], "history") == 0)
    {
        show_history();
        return 1;
    }

    /* jobs */
    if (strcmp(args[0], "jobs") == 0)
    {
        list_jobs();
        return 1;
    }

    return 0;
}