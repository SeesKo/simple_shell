#include "shell.h"

/**
 * exec_command - Executes a command given as input.
 * @input: The input command string to execute.
 * @exit_status: Pointer to an integer to store the
 * exit status of the command.
 */
void exec_command(char *input, int *exit_status)
{
	char *tokens[64]; /* Assuming 64 arguments max */
	int token_count;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Forking error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */
		parse_line(input, tokens, &token_count);

		if (tokens[0] == NULL)
			exit(EXIT_SUCCESS);

		find_executable(tokens[0], tokens);
		execute_command(tokens);
	}
	else
	{
		/* Parent process */
		int status;

		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
			*exit_status = WEXITSTATUS(status);
		else
			*exit_status = 1;
	}
}

/**
 * find_executable - Finds the executable path of a
 * command in the given tokens array.
 * @command: The command to find the executable path for.
 * @tokens: Array of strings containing the command
 * and its arguments.
 */
void find_executable(char *command, char *tokens[])
{
	if (access(command, X_OK) == -1)
	{
		char *path = getenv("PATH");
		char *path_copy = strdup(path);
		char *dir = strtok(path_copy, ":");

		while (dir != NULL)
		{
			char full_path[PATH_MAX];

			snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

			if (access(full_path, X_OK) == 0)
			{
				if (execve(full_path, tokens, NULL) != -1)
				{
					free(path_copy);
					return;
				}
			}
			dir = strtok(NULL, ":");
		}
		if (errno == ENOENT)
		{
			fprintf(stderr, "%s: command not recognized\n", command);
			exit(EXIT_FAILURE);
		}
		else
		{
			perror("Error in execve execution");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * execute_command - Executes a command using the
 * execve system call.
 * @tokens: Array of strings containing the command
 * and its arguments.
 */
void execute_command(char *tokens[])
{
	if (execve(tokens[0], tokens, NULL) == -1)
	{
		perror("Error in execve execution");
		exit(EXIT_FAILURE);
	}
}
