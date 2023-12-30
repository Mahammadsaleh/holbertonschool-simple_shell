#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
extern char **environ;

char **line_devider(char *buffer, char **arr);
char *get_input(void);
int execute(char *buffer);
#endif
