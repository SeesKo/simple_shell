#include "shell.h"

void setenv_variable(char **args)
{
    if (args[1] != NULL && args[2] != NULL)
    {
            /* 1 to overwrite if variable already exists, 0 otherwise */
        int overwrite = 1;

        if (setenv(args[1], args[2], overwrite) != 0)
        {
            perror("setenv failure");
        }
    }
    else
    {
        fprintf(stderr, "Error: Unable to set environment variable\n"
                        "Usage: setenv VARIABLE VALUE\n");
    }
}

void unsetenv_variable(char **args)
{
    if (args[1] != NULL)
    {
        if (unsetenv(args[1]) != 0)
        {
            perror("unsetenv failure");
        }
    }
    else
    {
        fprintf(stderr, "Error: Unable to unset environment variable\n"
                        "Usage: unsetenv VARIABLE\n");
    }
}
