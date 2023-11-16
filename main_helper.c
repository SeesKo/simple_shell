#include "shell.h"

void file_cmd_handle(FILE *file, char **directories, int *exit_status, Alias *aliases)
{
    char *command;
    char **args;
    char *previous_dir = NULL;

    while ((command = read_file(file)) != NULL)
    {
        args = parse_command(command, exit_status);

        if (strcmp(args[0], "exit") == 0)
        {
            if (args[1] != NULL)
                *exit_status = atoi(args[1]);

            cleanup_and_exit(command, args, directories, exit_status);
        }
        else if (strcmp(args[0], "env") == 0)
        {
            char **env = environ;
            while (*env)
            {
                write(STDOUT_FILENO, *env, strlen(*env));
                write(STDOUT_FILENO, "\n", 1);
                env++;
            }
        }
        else if (strcmp(args[0], "setenv") == 0)
            setenv_variable(args);
        else if (strcmp(args[0], "unsetenv") == 0)
            unsetenv_variable(args);
        else if (strcmp(args[0], "cd") == 0)
            change_dir(args, exit_status, &previous_dir);
        else if (strcmp(args[0], "alias") == 0)
            alias_cmd(args, aliases);
        else
            exec_cmd(args, directories, exit_status);

        cleanup_command_args(command, args);
    }
}

void interactive_cmd_handle(char **directories, int *exit_status, Alias *aliases)
{
    char *command;
    char **args;
    char *previous_dir = NULL;

    while (1)
    {
        prompt_me();
        command = get_input();

        if (!command)
            continue;
        args = parse_command(command, exit_status);
        if (strcmp(args[0], "exit") == 0)
        {
            if (args[1] != NULL)
                *exit_status = atoi(args[1]);
            cleanup_and_exit(command, args, NULL, exit_status);
        }
        else if (strcmp(args[0], "env") == 0)
        {
            char **env = environ;
            while (*env)
            {
                write(STDOUT_FILENO, *env, strlen(*env));
                write(STDOUT_FILENO, "\n", 1);
                env++;
            }
        }
        else if (strcmp(args[0], "setenv") == 0)
            setenv_variable(args);
        else if (strcmp(args[0], "unsetenv") == 0)
            unsetenv_variable(args);
        else if (strcmp(args[0], "cd") == 0)
            change_dir(args, exit_status, &previous_dir);
        else if (strcmp(args[0], "alias") == 0)
            alias_cmd(args, aliases);
        else
            exec_cmd(args, directories, exit_status);
        cleanup_command_args(command, args);
    }
}

void cleanup_and_exit(char *command, char **args, char **directories, int *exit_status)
{
    free(command);
    cleanup_command_args(NULL, args);
    free(directories);
    exit(*exit_status);
}

void cleanup_command_args(char *command, char **args)
{
    int i;

    free(command);
    for (i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}
