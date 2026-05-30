#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#include "shell.h"
#include "parser.h"
#include "executor.h"
#include "builtins.h"
#include "history.h"

#define MAX_INPUT 1024
#define MAX_ARGS 64

void run_shell(void)
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

    while (1)
    {
        while (waitpid(-1, NULL, WNOHANG) > 0)
        {
        }

        printf("myshell> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        if (strlen(input) <= 1)
            continue;

        add_to_history(input);

        parse_command(input, args);

        if (args[0] == NULL)
            continue;

        if (!handle_builtin(args))
        {
            execute_command(args);
        }
    }
}