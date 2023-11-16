#include "shell.h"

char **get_path(char *path)
{
    char *token, *trackerptr;
    static char *directories[MAX_DIR];
    int i = 0;

    token = safe_tok(path, ":", &trackerptr);
    while (token && i < MAX_DIR - 1)
    {
        directories[i] = token;
        i++;

        token = safe_tok(NULL, ":", &trackerptr);
    }

    /* Set last element to NULL to mark array end */
    directories[i] = NULL;

    return (directories);
}
