#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "redirection.h"

int handle_redirection(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
    {
        /* Output Redirection */
        if (strcmp(args[i], ">") == 0)
        {
            int fd = open(args[i + 1],
                          O_WRONLY | O_CREAT | O_TRUNC,
                          0644);

            if (fd < 0)
            {
                perror("open");
                return -1;
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);

            args[i] = NULL;
            return 1;
        }

        /* Input Redirection */
        if (strcmp(args[i], "<") == 0)
        {
            int fd = open(args[i + 1], O_RDONLY);

            if (fd < 0)
            {
                perror("open");
                return -1;
            }

            dup2(fd, STDIN_FILENO);
            close(fd);

            args[i] = NULL;
            return 1;
        }
    }

    return 0;
}