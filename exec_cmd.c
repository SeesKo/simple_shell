#include "shell.h"

/**
 * exec_cmd - Executes command based on arguments and directories.
 * @args: Array of command arguments.
 * @directories: Array of directories in the PATH.
 */
void exec_cmd(char **args, char **dir, int *exit_status)
{
        pid_t child_pid;
        char *cmd_path = exec_find(args[0], dir);

        if (cmd_path)
        {
                child_pid = fork();

                if (child_pid == -1)
                {
                        perror("fork failure");
                        *exit_status = 1;
                }
                else if (child_pid == 0)
                {
                        execve(cmd_path, args, NULL);
                        perror(args[0]);
                        exit(1);
                }
                else
                {
                        int status;
                        waitpid(child_pid, &status, 0);

                        if (WIFEXITED(status))
                                *exit_status = WEXITSTATUS(status);
                        else
                                *exit_status = 1;
                        free(cmd_path);
                }
        }
        else
        {
                write(STDERR_FILENO, args[0], strlen(args[0]));
                write(STDERR_FILENO, ": not found\n", 12);

                *exit_status = 1;
        }
}
