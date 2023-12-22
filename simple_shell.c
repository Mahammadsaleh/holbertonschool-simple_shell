#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
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

	arr = malloc(strlen(buffer) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
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
 * shell_input - input part
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
		return (NULL);
	}
	arr = line_devider(*buffer);
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

	for (i = 0; arr[i] != NULL; i++)
	{
		free(arr[i]);
	}
	free(arr);
}
/**
 * main - main func
 *
 * Return: int
 */
int main(void)
{
	char *buffer = NULL;
	size_t len = 1024;
	int read;
	pid_t pid;
	char **arr;
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		read = getline(&buffer, &len, stdin);
		if (read == -1)
			break;
		arr = line_devider(buffer);
		if (arr[0] == NULL)
		{
			free(arr);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			if (execve(arr[0],arr, NULL) == -1)
			{
				perror("ERROR");
				exit(1);
			}
		}
		else if (pid > 0)
		{
			int status;
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
		for (i = 0; arr[i] != NULL; i++)
		{
			free(arr[i]);
		}
		free(arr);
	}
	free(buffer);
	return (0);
}
