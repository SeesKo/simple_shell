#include "shell.h"

char *get_input(void)
{
    char *input = NULL;
    size_t size = 0;
    ssize_t chars_read;

    chars_read = get_line(&input, &size, stdin);

    if (chars_read == -1)
    {
        if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);

        free(input);
        return (NULL);
    }

    if (chars_read > 0 && input[chars_read - 1] == '\n')
    {
        input[chars_read - 1] = '\0';

        /* Check if input consists of newline char only */
        if (chars_read == 1)
        {
            free(input);
            return (NULL);
        }
    }

    return (input);
}
