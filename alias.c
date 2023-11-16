#include "shell.h"

/**
 * create_alias - Creates a new alias with the given name and value.
 * @aliases: The array of Alias structures.
 * @name: The name of the new alias.
 * @value: The value associated with the new alias.
 *
 * Return: 0 on success, -1 if the maximum alias limit is reached.
 */
int create_alias(Alias *aliases, const char *name, const char *value)
{
	int i;

	for (i = 0; i < MAX_ALIASES; ++i)
	{
		if (aliases[i].name[0] == '\0')
		{
			/* Exit function if alias created successfully */
			strcpy(aliases[i].name, name);
			strcpy(aliases[i].value, value);
			return (0);
		}
	}
	return (-1); /* Error: MAX alias limit reached */
}

/**
 * update_alias - Updates the specified alias with a new name and value.
 * @alias: The Alias structure to be updated.
 * @name: The new name for the alias.
 * @value: The new value associated with the alias.
 */
void update_alias(Alias *alias, const char *name, const char *value)
{
	strcpy(alias->name, name);
	strcpy(alias->value, value);
}

/**
 * find_alias_index - Searches for the index of the specified alias name.
 * @name: The name of the alias to search for.
 * @aliases: The array of Alias structures.
 *
 * Return: The index of the alias if found, -1 otherwise.
 */
int find_alias_index(const char *name, Alias *aliases)
{
	int i;

	for (i = 0; i < MAX_ALIASES; ++i)
	{
		/* If alias found, return index */
		if (aliases[i].name[0] != '\0' && strcmp(aliases[i].name, name) == 0)
			return (i);
	}
	/* If alias not found */
	return (-1);
}

/**
 * print_alias_value - Prints the value associated with specified alias.
 * @name: The name of the alias to print.
 * @aliases: The array of Alias structures.
 */
void print_alias_value(const char *name, Alias *aliases)
{
	int index = find_alias_index(name, aliases);

	if (index != -1)
		printf("%s=%s\n", aliases[index].name, aliases[index].value);
	else
		fprintf(stderr, "Error: Alias '%s' not found\n", name);
}
