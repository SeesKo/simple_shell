#include "shell.h"

int change_directory(const char *target_dir, int *exit_status)
{
    if (chdir(target_dir) != 0)
    {
        perror("directory change failure");
        *exit_status = 1;
        return 1;
    }

    if (setenv("PWD", getcwd(NULL, 0), 1) != 0)
    {
        perror("env variable setting failed");
        *exit_status = 1;
        return 1;
    }

    return 0;
}

void update_previous_directory(const char *current_dir, char **previous_dir, int *exit_status)
{
    free(*previous_dir);
    *previous_dir = strdup(current_dir);

    if (*previous_dir == NULL)
    {
        perror("duplication failure");
        *exit_status = 1;
    }
}

void change_dir(char **args, int *exit_status, char **previous_dir)
{
    char *target_dir = args[1];
    char current_dir[MAX_PATH_LENGTH];

    if (target_dir == NULL || target_dir[0] == '~')
    {
        target_dir = getenv("HOME");
        if (target_dir == NULL)
        {
            fprintf(stderr, "Error: HOME environment variable not set\n");
            *exit_status = 1;
            return;
        }
    }
    else if (strcmp(target_dir, "-") == 0)
    {
        if (*previous_dir == NULL)
        {
            fprintf(stderr, "Error: Previous directory not set\n");
            *exit_status = 1;
            return;
        }
        target_dir = *previous_dir;
    }

    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        perror("No such file or directory");
        *exit_status = 1;
        return;
    }

    if (change_directory(target_dir, exit_status) != 0)
    {
        return;
    }

    update_previous_directory(current_dir, previous_dir, exit_status);
}
