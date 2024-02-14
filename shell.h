#ifndef SHELL_H
#define SHELL_H

/* STANDARD LIBRARY HEADERS */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>

/* ENVIRONMENT VARIABLES */
extern char **environ;

#define MAX_TOKENS 64

/* USER-DEFINED FUNCTION PROTOTYPES */
void prompt_me(void);
char *read_line(void);
void exec_command(char *input, int *exit_status);
void find_executable(char *command, char *tokens[]);
void execute_command(char *tokens[]);
void parse_line(char *input, char **tokens, int *token_count);
void handle_builtin(char *command, int *exit_status);
void exit_shell(int *exit_status);
void print_env(void);

#endif /* SHELL_H */
