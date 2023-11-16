# ALX Project 0x16. C - Simple Shell

This README file provides the description of the project.

## Requirements
### General

    Allowed editors: vi, vim, emacs.
    All files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89.
    All files should end with a new line.
    A README.md file, at the root of the folder of the project is mandatory.
    The code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl.
    The shell should not have any memory leaks.
    No more than 5 functions per file.
    All header files should be include guarded.
    Use system calls only when you need to (why?).
    Write a README with the description of your project.
    An AUTHORS file should be present at the root of the repository, listing all individuals having contributed content to the repository. Format, see Docker.

## Overview

Simple Shell is a basic Unix shell written in C that provides a command-line interface to interact with your system. It supports common shell commands and features, making it a handy tool for running commands and managing your system.

## Features

- Command execution
- Built-in commands (e.g., `ls`, `exit`, `env`)
- Dynamic environment variable display
- PATH-based executable discovery

## Usage

The Simple Shell provides a command-line interface that you can use to interact with your system. Here are some example commands:

## Development Guidelines

If you're planning to contribute to the Simple Shell project, please adhere to the following guidelines:

### Allowed Functions and System Calls

Use of the following functions and system calls was encouraged:

- `access`
- `chdir`
- `close`
- `closedir`
- `execve`
- `exit`
- `_exit`
- `fflush`
- `fork`
- `free`
- `getcwd`
- `getline`
- `getpid`
- `isatty`
- `kill`
- `malloc`
- `open`
- `opendir`
- `perror`
- `read`
- `readdir`
- `signal`
- `stat`
- `lstat`
- `fstat`
- `strtok`
- `wait`
- `waitpid`
- `wait3`
- `wait4`
- `write`

Some other functions or system calls not listed here may be used although functions like `getline` and `strtok`
were prohibited midway through the project.
