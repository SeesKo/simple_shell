#include "shell.h"

/**
 * printchar - Prints a character to the standard output.
 * @c: The character to print.
 * Return: 1 on success.
 */
int printchar(char c)
{
        return (write(1, &c, 1));
}

/**
 * printstr - Prints a string.
 * @str: Pointer to a character.
 */
void printstr(char *str)
{
        int i;

        for (i = 0; str[i] != '\0'; i++)
        {
                printchar(str[i]);
        }
}
