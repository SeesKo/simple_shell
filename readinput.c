#include "shell.h"

void display_prompt(void) {
    printf("#cisfun$ ");
    fflush(stdout);
}

char *read_user_input(void) {
    char *buffer = NULL;
    size_t bufsize = 0;

    if (getline(&buffer, &bufsize, stdin) == -1) {
        free(buffer);
        exit(EXIT_SUCCESS);
    }

    buffer[_strlen(buffer) - 1] = '\0';

    return buffer;
}

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
	    int i = 0;
        char *token;
        char **argv = (char **)malloc(BUFFER_SIZE * sizeof(char *));
        if (argv == NULL) 
        {
            perror("malloc");
            free(command);
            exit(EXIT_FAILURE);
        }
        token = strtok(command, " ");
        while (token != NULL) {
            argv[i++] = token;
            token = strtok(NULL, " ");
        }
        argv[i] = NULL;
        if (execvp(argv[0], argv) == -1) 
        {
            perror(argv[0]);
            free(command);
            free(argv);
            exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) 
            fprintf(stderr, "./shell: %s: command not found\n", command);
    }
}
