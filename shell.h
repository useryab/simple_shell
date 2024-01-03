#ifndef SHELL_H
#define SHELL_H

#define MAX_LENGTH 100

/* Header files */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>


char *_strcat(char *dest, char *src);
char *get_path(char *command);
char **get_arg(char *buffer);
void _free(char ***arg);
void print_arg(char **arg);

#endif
