#include "shell.h"

/**
 * str_tok - Custom string tokenization function
 * @str: The input string to be tokenized
 * @delimiters: The set of delimiter characters for tokenization
 *
 * Return: A pointer to a token(if the token is found), NULL if end of
 * string is reached or no more tokens are found.
 */
char *str_tok(char *str, const char *delimiters)
{
	/* Static var to maintain state between calls */
    static char *endToken = NULL;
    char *token; /* Pointer to the token */

    /* If called with a new string, update lastToken */
    if (str != NULL)
        endToken = str;
    else
    {
        /* If called with NULL, continue from the last token */
        if (endToken == NULL)
            return (NULL); /* No more tokens */
        str = endToken;
    }

    /* Skip leading delimiters */
    str += strspn(str, delimiters);

    /* Check if we reached the end of the string */
    if (*str == '\0')
    {
        endToken = NULL; /* No more tokens */
        return (NULL);
    }

    /* Find the end of the token */
    token = str;
    str = strpbrk(token, delimiters);

    if (str != NULL)
    {
        /* Found a delimiter, replace it with null character */
        *str = '\0';
        endToken = str + 1; /* Move lastToken to the next character */
    }
    else
        endToken = NULL;

    return (token);
}

/**
 * safe_tok - Custom reentrant string tokenization function
 * @str: The input string to be tokenized
 * @delimiters: Set of delimiter characters for tokenization.
 * @saveptr: Pointer to a char pointer to store the state information.
 *
 * Return: A pointer to a token(if the token is found), NULL if end of
 * string is reached or no more tokens are found.
 */
char *safe_tok(char *str, const char *delimiters, char **trackerptr)
{
    char *token;

    if (str != NULL)
        *trackerptr = str;
    else
    {
        if (*trackerptr == NULL)
            return (NULL);
        str = *trackerptr;
    }

    /* Skip leading delimiters */
    str += strspn(str, delimiters);

    /* Check if we reached the end of the string */
    if (*str == '\0')
    {
        *trackerptr = NULL;
        return (NULL);
    }

    /* Find the end of the token */
    token = str;
    str = strpbrk(token, delimiters);

    if (str != NULL)
    {
        /* Found a delimiter, replace it with null character */
        *str = '\0';
        *trackerptr = str + 1;
    }
    else
        *trackerptr = NULL;

    return (token);
}
