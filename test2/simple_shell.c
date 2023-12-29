#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#define CHAR_BUFFER 1024
/**
 * line_devider - devide the line
 * @buffer: string
 *
 * Return: char ptr to ptr
 */
char **line_devider(char *buffer)
{
	char **arr;
	char *token;
	int i = 0;

	arr = malloc((strlen(buffer) + 1) * sizeof(char *));
	if (arr == NULL)
	{
		perror("ERROR");
		exit(1);
	}
	token = strtok(buffer, " \n\t");
	while (token)
	{
		arr[i] = strdup(token);
		if (arr[i] == NULL)
		{
			perror("ERROR");
			exit(1);
		}
		i++;
		token = strtok(NULL, " \n\t");
	}
	arr[i] = NULL;
	return (arr);
}
/**
 * free_array - free array memory
 * @arr: buffer
 *
 * Return - nothing
 */
void free_array(char **arr)
{
	int i;

	if (arr == NULL)
		return;
	for (i = 0; arr[i] != NULL; i++)
	{
		free(arr[i]);
	}
	free(arr);
}
/**
 * path_handler - path handler
 * @file_name: name of file
 *
 * @path: path
 *
 * return: file_name
 */
char *path_handler(char *cmd, char *path)
{
    char *p = strtok(path, ":");
    while(p != NULL)
    {
        DIR *d = opendir(p);
        if (d != NULL)
        {
            struct dirent *dir;
            while ((dir = readdir(d)) != NULL)
            {
                if (strcmp(dir->d_name, cmd) == 0)
                {
                    char *full_path = malloc(strlen(p) + strlen(cmd) + 2);
                    strcpy(full_path, p);
                    strcat(full_path, "/");
                    strcat(full_path, cmd);
                    closedir(d);
                    return full_path;
                }
            }
            closedir(d);
        }
        p = strtok(NULL, ":");
    }
    return NULL;
}
/**
 * get_input - input part
 * @len: len
 * @buffer: buff
 *
 * Return: void
 */
char **get_input(char *path)
{
	char *buffer = NULL;
	size_t len = 0;
	size_t read;
	char **arr;

	if (isatty(STDIN_FILENO))
		printf("$ ");
	read = getline(&buffer, &len, stdin);
	if (read == -1)
	{
		free(buffer);
		return (NULL);
	}
	arr = line_devider(buffer);
	char *original_command = strdup(arr[0]);
	char *full_path = path_handler(arr[0], path);
    if (arr[0] != NULL && full_path == NULL)
    {
        char error_message[CHAR_BUFFER];
        fprintf(stderr, "./hsh: 1: %s: not found\n", original_command);
        free_array(arr);
        exit(127);
    }
    free(arr[0]);
    arr[0] = full_path;
	return (arr);
}
/**
 * main - main func
 *
 * Return: int
 */
int main(int argc, char **argv)
{
	extern char **environ;
	char **arr;
	int status = 0;
	pid_t pid;
	char *path = getenv("PATH");

	while (1)
	{
		arr = get_input(path);
		if (arr == NULL)
			break;
		if (arr[0] == NULL)
		{
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			if (strcmp(arr[0], "exit") == 0)
        {
            free_array(arr);
            exit(EXIT_SUCCESS);
        }
        if (execve(arr[0], arr, environ) == -1)
        {
            perror("ERROR");
            free_array(arr);
            exit(1);
        }
		}
		else if (pid > 0)
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("ERROR");
			}
			if (WIFEXITED(status))
			{
				int exit_status = WEXITSTATUS(status);
				if (exit_status == 127)
				{
					exit(127);
				}
			}
		}
		else
		{
			perror("ERROR");
		}
		if (pid == -1)
			perror("ERROR");
		free_array(arr);
	}
	return (status);
}

