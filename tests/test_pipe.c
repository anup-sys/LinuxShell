#include <stdio.h>
#include "pipes.h"

int main(void)
{
    char *args[] = {
        "ls",
        "|",
        "grep",
        "txt",
        NULL
    };

    if (has_pipe(args))
    {
        printf("Pipe detected successfully.\n");
    }
    else
    {
        printf("Pipe detection failed.\n");
    }

    return 0;
}