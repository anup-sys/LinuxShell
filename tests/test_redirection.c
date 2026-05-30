#include <stdio.h>
#include "redirection.h"

int main(void)
{
    char *args[] = {
        "ls",
        ">",
        "output.txt",
        NULL
    };

    int result = handle_redirection(args);

    printf("Redirection result = %d\n", result);

    return 0;
}