#include <stdio.h>
#include "parser.h"

int main(void)
{
    char input[] = "ls -l";
    char *args[10];

    parse_command(input, args);

    printf("Parser Test:\n");

    for (int i = 0; args[i] != NULL; i++)
    {
        printf("args[%d] = %s\n", i, args[i]);
    }

    return 0;
}