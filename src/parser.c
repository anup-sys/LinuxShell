#include <string.h>
#include "parser.h"

void parse_command(char *input, char **args)
{
    int i = 0;

    char *token = strtok(input, " \t\n");

    while (token != NULL)
    {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }

    args[i] = NULL;
}