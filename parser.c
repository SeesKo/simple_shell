#include "shell.h"

/**
 * change_token - Replaces a token in input string.
 * @input: User input.
 * @token: Token to replace.
 * @replacer: String to replace the token with.
 *
 * Return: Modified input string.
 */
static char *change_token(char *input, const char *token, const char *replacer)
{
    char *result;
    char *token_pos;

    result = strdup(input);
    if (result == NULL)
    {
        perror("memory allocation failure");
        exit(1);
    }

    token_pos = strstr(result, token);
    while (token_pos != NULL)
    {
        memmove(token_pos + strlen(replacer), token_pos + strlen(token),
                strlen(token_pos + strlen(token)) + 1);
        memcpy(token_pos, replacer, strlen(replacer));
        token_pos = strstr(token_pos + strlen(replacer), token);
    }

    return (result);
}

/**
 * sub_special_tokens - Replaces special tokens in input string.
 * @input: User input.
 * @exit_status: Exit status to replace '$?' with.
 *
 * Return: Modified input string
 */
static char *sub_special_tokens(char *input, int exit_status)
{
    char *path;
    char *pid_str;

    /* Replace $? with the exit status */
    char *exit_status_str = malloc(25);
    if (exit_status_str == NULL)
    {
        perror("memory allocation failure");
        exit(1);
    }
    snprintf(exit_status_str, 25, "%d", exit_status);
    input = change_token(input, "$?", exit_status_str);

    /* Replace $PATH with the actual PATH */
    path = getenv("PATH");
    input = change_token(input, "$PATH", path);

    /* Replace $$ with the process ID */
    pid_str = malloc(25);
    if (pid_str == NULL)
    {
        perror("memory allocation failure");
        exit(1);
    }
    snprintf(pid_str, 25, "%d", getpid());
    input = change_token(input, "$$", pid_str);

    free(exit_status_str);
    free(pid_str);

    return (input);
}

/**
 * parse_command - Parses user input into array of cmd arguments.
 * @input: User input.
 * @exit_status: Exit status.
 *
 * Return: Array of command arguments, NULL on failure.
 */
char **parse_command(char *input, int *exit_status)
{
    int arg_count = 0;
    char **args = NULL;
    char *token;
    char **temp;

    input = sub_special_tokens(input, *exit_status);

    token = str_tok(input, " ");
    while (token != NULL)
    {
        /* Check for and remove comments */
        char *comment = strchr(token, '#');
        if (comment != NULL)
        {
            *comment = '\0'; /* Nullify the comment */
            break; /* Stop parsing after encountering a comment */
        }

        temp = realloc(args, sizeof(char *) * (arg_count + 2));
        if (!temp)
        {
            perror("memory allocation failure");
            exit(1);
        }

        args = temp;

        args[arg_count] = strdup(token);
        if (!args[arg_count])
        {
            perror("memory allocation failure");
            exit(1);
        }

        args[arg_count + 1] = NULL;

        arg_count++;

        token = str_tok(NULL, " ");
    }

    return (args);
}
