#include "shell.h"

int main(int argc, char *argv[])
{
    char *path = getenv("PATH");
    char **directories = get_path(path);
    int exit_status = 0;
    char *previous_dir = NULL;

    Alias aliases[MAX_ALIASES];
    init_alias(aliases);

    if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
            perror("Error opening file");
            return (1);
        }

        file_cmd_handle(file, directories, &exit_status, aliases);

        fclose(file);

        free(previous_dir);
        return (exit_status);
    }

    interactive_cmd_handle(directories, &exit_status, aliases);

    free(previous_dir);
    return (exit_status);
}
