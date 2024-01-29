#include "shell.h"

/**
 * prompt_me - Displays the shell prompt.
 */
void prompt_me(void)
{
	printf("myshell> ");
	fflush(stdout);
}

/**
 * read_line - Reads a line of input from the user.
 *
 * Return: A dynamically allocated string containing
 * the user input or NULL if an error occurs.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t characters;

	/* Reading user input */
	characters = getline(&line, &bufsize, stdin);

	/* Handle end-of-file condition */
	if (characters == -1)
	{
		free(line);
		return (NULL);
	}

	/* Remove newline character if present */
	if (line[characters - 1] == '\n')
	{
		line[characters - 1] = '\0';
	}

	return (line);
}
