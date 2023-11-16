#include "shell.h"

ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
    static char buffer[CHAR_BUFFER];
    static size_t buffer_index = 0;
    static size_t buffer_size = 0;
    size_t len = 0;
    char c;
    char *temp;

    if (stream == NULL)
    {
            fprintf(stderr, "Error: NULL stream\n");
            return (-1);
    }

    if (*lineptr == NULL || *n == 0)
            *n = CHAR_BUFFER;

    temp = realloc(*lineptr, *n);
    if (!temp)
    {
        perror("memory reallocation failure");
        exit(EXIT_FAILURE);
    }
    *lineptr = temp;

    while (1)
    {
        /* Check if buffer is empty, read more characters if needed */
        if (buffer_index == buffer_size)
        {
            ssize_t bytesRead = read(fileno(stream), buffer, CHAR_BUFFER);

            if (bytesRead <= 0)
            {
                if (len == 0)
                        return (-1); /* No input received */

                break;
            }

            buffer_size = bytesRead;
            buffer_index = 0;
        }

        /* Copy characters from buffer to lineptr */
        c = buffer[buffer_index++];

        if (c == EOF)
        {
            if (len == 0)
                    return -1; /* No input received */

            break;
        }

        /* Check if reallocation is needed */
        if (len + 1 >= *n)
        {
            *n += CHAR_BUFFER;
            temp = realloc(*lineptr, *n);

            if (!temp)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }

            *lineptr = temp;
        }

        (*lineptr)[len++] = c;

        if (c == '\n')
                break;
    }

    /* Null-terminate the line */
    if (len + 1 >= *n)
    {
        *n += 1;
        temp = realloc(*lineptr, *n);
        if (!temp)
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        *lineptr = temp;
    }
    (*lineptr)[len] = '\0';

    return (len);
}
