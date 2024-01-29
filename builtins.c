#include "shell.h"

/**
 * handle_builtin - Handles built-in shell commands
 * or executes other commands.
 * @command: The command to handle.
 * @exit_status: Pointer to an integer to store the
 * exit status of the command.
 */
void handle_builtin(char *command, int *exit_status)
{
	if (strcmp(command, "exit") == 0)
		exit_shell(exit_status);
	else if (strcmp(command, "env") == 0)
		print_env();
	else
		exec_command(command, exit_status);
}

/**
 * exit_shell - Exits the shell with the specified exit status.
 * @exit_status: Pointer to an integer containing the exit status.
 */
void exit_shell(int *exit_status)
{
	exit(*exit_status);
}

/**
 * print_env - Prints the environment variables.
 */
void print_env(void)
{
	char **env_ptr = environ;

	while (*env_ptr != NULL)
	{
		printf("%s\n", *env_ptr);
		env_ptr++;
	}
}
