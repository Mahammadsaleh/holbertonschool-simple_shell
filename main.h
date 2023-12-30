#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
extern char **environ;

char **line_devider(char *buffer, char **arr);
char *get_input(void);
void free_array(char **arr);
int path_handler(char *buffer);
#endif
