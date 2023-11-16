#include "shell.h"

char *read_file(FILE *file)
{
    char *buffer = NULL;
    size_t buff_size = 0;
    ssize_t char_count;

    /* Read a line from the file */
    char_count = get_line(&buffer, &buff_size, file);

    /* Check for end of file */
    if (char_count == -1)
    {
        free(buffer);
        return (NULL);
    }

    /* Remove newline character at the end */
    if (char_count > 0 && buffer[char_count - 1] == '\n')
    {
        buffer[char_count - 1] = '\0';
    }

    return (buffer);
}
