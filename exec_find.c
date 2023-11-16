#include "shell.h"

/**
 * exec_find - Finds the full path of an executable in the PATH.
 * @command: The command to search for.
 * @directories: Array of directories in the PATH.
 *
 * Return: Full path of the executable, NULL if not found.
 */
char *exec_find(char *cmd, char **directories)
{
        char *path, *cmd_path = NULL;
        int i = 0;

        while (directories[i])
        {
                path = malloc(strlen(directories[i]) + 1 + strlen(cmd) + 1);
                if (!path)
                {
                        perror("memory allocation failure");
                        exit(1);
                }
                snprintf(path, strlen(directories[i]) + 1 + strlen(cmd) + 1,
                                "%s/%s", directories[i], cmd);
                if (access(path, X_OK) == 0)
                {
                        cmd_path = strdup(path);
                        if (!cmd_path)
                        {
                                perror("duplication failure");
                                exit(1);
                        }
                        break;
                }

                if (access(cmd, X_OK) == 0)
                {
                        cmd_path = strdup(cmd);
                        if (!cmd_path)
                        {
                                perror("duplication failure");
                                exit(1);
                        }
                        break;
                }

                free(path);
                i++;
        }
        return (cmd_path);
}
