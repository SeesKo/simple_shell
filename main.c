#include "shell.h"

/**
 * main - Main function for the shell.
 *
 * Return: 0 on success.
 */
int main(void)
{
	char *input;
	int exit_status = 0;
	bool is_interactive = isatty(STDIN_FILENO);

	/* Interactive mode */
	if (is_interactive)
	{
		while (1)
		{
			/* Prompt display only in interactive */
			prompt_me();
			/* Reading user input */
			input = read_line();

			/* Check for End-Of-File(EOF) condition */
			if (input == NULL)
			{
				printf("\n");
				break;
			}

			/* Execute the command */
			handle_builtin(input, &exit_status);

			/* Free the allocated memory */
			free(input);
		}
	}
	/* Non-interactive mode */
	else
	{
		input = read_line();

		handle_builtin(input, &exit_status);

		free(input);
	}

	return (0);
}

/**
 * parse_line - Tokenizes input to split command and arguments.
 * @input: The input command string to parse.
 * @tokens: Array to store the parsed tokens.
 * @token_count: Pointer to an integer to store the count of tokens.
 */
void parse_line(char *input, char **tokens, int *token_count)
{
	char *token;
	*token_count = 0;

	/* Tokenize input to split command and arguments */
	token = strtok(input, " ");
	while (token != NULL)
	{
		tokens[(*token_count)++] = token;
		token = strtok(NULL, " ");
	}

	/* Null-terminate array */
	tokens[*token_count] = NULL;
}
