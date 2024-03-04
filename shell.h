#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

void display_prompt(void);
char *read_user_input(void);
void execute_command(char *command);
size_t _strlen(const char *str);

#endif /* SHELL_H */
