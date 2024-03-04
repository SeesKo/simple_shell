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

void execute_command(char *command) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        free(command);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        char **argv = (char **)malloc(2 * sizeof(char *));
        if (argv == NULL) {
            perror("malloc");
            free(command);
            exit(EXIT_FAILURE);
        }

        argv[0] = command;
        argv[1] = NULL;

        if (execve(command, argv, NULL) == -1) {
            perror(command);
            free(command);
            free(argv);
            exit(EXIT_FAILURE);
        }

        free(argv);
    } else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            fprintf(stderr, "./shell: %s: command not found\n", command);
        }
    }
}
