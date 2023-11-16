#ifndef SHELL_H
#define SHELL_H

/* Standard Library Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

/* MACROS */
#define MAX_DIR 100
#define BUFFER_SIZE 1024
#define MAX_PATH_LENGTH 1024
#define CHAR_BUFFER 256
#define MAX_ALIAS_NAME 20
#define MAX_ALIAS_VALUE 100
#define MAX_ALIASES 20
#define NO_SEPARATOR 0
#define SEMICOLON 1
#define AND 2
#define OR 3

/**
 * struct alias - Represents an alias with a name and
 * a corresponding value.
 * @name: Name of the alias, stored in character array.
 * @value: The value associated with the alias, stored
 * in a character array.
 *
 * Description: Alias struct is designed to store info
 * about an alias.
 */
typedef struct alias
{
	char name[MAX_ALIAS_NAME];
	char value[MAX_ALIAS_VALUE];
} Alias;

/* User-Defined Function Prototypes */
int printchar(char c);
void printstr(char *str);
void prompt_me(void);

ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
char *str_tok(char *str, const char *delimiters);
char *safe_tok(char *str, const char *delimiters, char **saveptr);

void change_dir(char **args, int *exit_status, char **previous_dir);

char *read_file(FILE *file);
char **get_path(char *path);
char *exec_find(char *cmd, char **directories);
char *get_input(void);

char **parse_command(char *input, int *exit_status);

void exec_cmd(char **args, char **dir, int *exit_status);
void setenv_variable(char **args);
void unsetenv_variable(char **args);

void file_cmd_handle(FILE *file, char **directories,
		int *exit_status, Alias *aliases);
void interactive_cmd_handle(char **directories,
		int *exit_status, Alias *aliases);
void cleanup_and_exit(char *command, char **args,
		char **directories, int *exit_status);
void cleanup_command_args(char *command, char **args);

int find_alias_index(const char *name, Alias *aliases);
void update_alias(Alias *alias, const char *name, const char *value);
int create_alias(Alias *aliases, const char *name, const char *value);
void print_alias_value(const char *name, Alias *aliases);
void alias_cmd(char **args, Alias *aliases);
void init_alias(Alias *aliases);

/* Environment Variable Declarations */
extern char **environ;

#endif /* SHELL_H */
