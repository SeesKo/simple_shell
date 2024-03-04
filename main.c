#include "shell.h"

int main(void) {
    char *command;

    while (1) {
        display_prompt();
        command = read_user_input();

        if (_strlen(command) > 0) {
            execute_command(command);
        }

        free(command);
    }

    return 0;
}
