#include "shell.h"

/**
 * display_prompt - Displays prompt.
 */
void display_prompt(void)
{
	printf("($) ");
	fflush(stdout);
}

/**
 * read_user_input - Reads a line of input from the user.
 *
 * Return: A dynamically allocated string containing
 * the user input or NULL if an error occurs.
 */
char *read_user_input(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;

	if (getline(&buffer, &bufsize, stdin) == -1)
	{
		printf("\n");
		free(buffer);
		exit(EXIT_SUCCESS);
	}

	buffer[strlen(buffer) - 1] = '\0';

	return (buffer);
}

/**
 * execute_command - Executes a command using the
 * execve system call.
 * @command: The command to find the executable path for.
 */
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(command);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		char **argv = (char **)malloc(2 * sizeof(char *));

		if (argv == NULL)
		{
			perror("malloc");
			free(command);
			exit(EXIT_FAILURE);
		}
		argv[0] = command;
		argv[1] = NULL;
		if (execve(command, argv, NULL) == -1)
		{
			perror("execve");
			free(command);
			free(argv);
			exit(EXIT_FAILURE);
		}
		free(argv);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
			fprintf(stderr, "%s: command not found\n", command);
	}
}

/**
 * main - Main function for the shell.
 *
 * Return: 0 on success.
 */
int main(void)
{
	char *command;

	while (1)
	{
		display_prompt();
		command = read_user_input();
		execute_command(command);
		free(command);
	}

	free(command);

	return (0);
}
