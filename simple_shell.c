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
	int i = 0, k;

	arr = malloc(250 * sizeof(char *));
	for (k = 0; k < 250; k++)
	{
		arr[i] = NULL;
	}

	if (arr == NULL)
		return (NULL);
	token = strtok(buffer," \n\t");
	while (token)
	{
		arr[i] = malloc(strlen(buffer));
		arr[i] = strdup(token);
		if (arr[i] == NULL)
		{
			perror("ERROR");
				exit(1);
		}
		i++;
		token = strtok(NULL," \n\t");
	}
	arr[i] = NULL;
	return (arr);
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
		{
			break;
		}
		arr = line_devider(buffer);
		pid = fork();
		if (pid == 0)
		{
			free(buffer);
			if (execve(arr[0],arr, NULL) == -1)
			{
	                	for (i = 0; arr[i] != NULL; i++)
                		{
                        		free(arr[i]);
               			}
                		free(arr);
				exit(1);
			}
		}
		else
		{
			wait(NULL);
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
