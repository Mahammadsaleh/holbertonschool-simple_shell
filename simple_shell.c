#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#define CHAR_BUFFER 1024
/**
 * line_divider - divide the line
 * @buffer: string
 *
 * Return: char ptr to ptr
 */
char **line_divider(char *buffer)
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
	return arr;
}
/**
 * get_input - input part
 * @len: len
 * @buffer: buff
 *
 * Return: void
 */
char **get_input(char **buffer, size_t *len)
{
	int read;
	char **arr;
	if (isatty(STDIN_FILENO))
		printf("$ ");
	read = getline(buffer, len, stdin);
	if (read == -1)
	{
		return NULL;
	}
	arr = line_divider(*buffer);
	return arr;
}
/**
 * free_array - free array memory
 * @arr: buffer
 *
 * Return: nothing
 */
void free_array(char ***arr)
{
	int i;
	for (i = 0; (*arr)[i] != NULL; i++)
	{
		free((*arr)[i]);
	}
	free(*arr);
}
char *path_handler(char *file_name)
{
	char *path = getenv("PATH");
	char *token, *cmd;
	cmd = malloc(strlen(file_name) + strlen(path) + 2);
	if (cmd == NULL)
	{
		perror("ERROR");
		exit(1);
	}
	token = strtok(path, ":");
	if (file_name[0] == '/')
	{
		if (access(file_name, X_OK) == 0)
		{
			return strdup(file_name);
		}
		return NULL;
	}
	while (token)
	{
		snprintf(cmd, strlen(file_name) + strlen(token) + 2, "%s/%s", token, file_name);
		if (access(cmd, X_OK) == 0)
		{
			return cmd;
		}
		token = strtok(NULL, ":");
	}
	free(cmd);
	return strdup(file_name);
}
/**
 * main - main func
 *
 * Return: int
 */
int main(void)
{
	char *buffer = NULL, **arr;
	size_t len = 1024;
	int status;
	pid_t pid;
	while (1)
	{
		arr = get_input(&buffer, &len);
		if (arr == NULL)
			break;
		if (arr[0] == NULL)
		{
			free_array(&arr);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			arr[0] = path_handler(arr[0]);
			if (execve(arr[0], arr, NULL) == -1)
			{
				perror("ERROR");
				exit(1);
			}
		}
		else if (pid > 0)
		{
			if (wait(&status) == -1)
			{
				perror("ERROR");
			}
		}
		else
		{
			perror("ERROR");
		}
		if (pid == -1)
			perror("ERROR");
		free_array(&arr);
	}
	free(buffer);
	return 0;
}
