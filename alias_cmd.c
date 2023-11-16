#include "shell.h"

void init_alias(Alias *aliases)
{
        int i;

        for (i = 0; i < MAX_ALIASES; ++i)
        {
                aliases[i].name[0] = '\0';
                aliases[i].value[0] = '\0';
        }
}

void alias_cmd(char **args, Alias *aliases)
{
    int i;
    char *name, *value;
    int index;
    /* Print all aliases if no argument */
    if (args[1] == NULL)
    {
        for (i = 0; i < MAX_ALIASES; ++i)
        {
            if (aliases[i].name[0] != '\0')
                printf("%s='%s'\n", aliases[i].name, aliases[i].value);
        }
    }
    else
    {
        if (strchr(args[1], '=') != NULL)
        {
            /* Parse and create/update the alias */
            name = strtok(args[1], "=");
            value = strtok(NULL, "=");
            create_alias(aliases, name, value);
            index = find_alias_index(name, aliases);

            if (index != -1)
                    update_alias(&aliases[index], name, value);
            else
                    create_alias(aliases, name, value);
        }
        else
        {
                /* Print corresponding aliases for every argument */
                for (i = 1; args[i] != NULL; ++i)
                        print_alias_value(args[i], aliases);
        }
    }
}
