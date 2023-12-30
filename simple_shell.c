#include <stdio.h>
#include <errno.h>
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
char **line_devider(char *buffer, char **arr)
{
	char *token;
	int i = 0;

	token = strtok(buffer, " \n\t");
	while (token != NULL && i < 63)
	{
		arr[i++] = token;
		token = strtok(NULL, " \n\t");
	}
	arr[i++] = NULL;
	return (arr);
}
/**
 * get_input - input part
 * @len: len
 * @buffer: buff
 *
 * Return: void
 */
char *get_input(void)
{
	char *buffer = NULL;
	size_t len = 0;
	int read;

	if (isatty(STDIN_FILENO))
		printf("$ ");
	read = getline(&buffer, &len, stdin);
	if (read == -1)
	{
		free(buffer);
		return (NULL);
	}
	if (buffer[read - 1] == '\n')
		buffer[read - 1] = '\0';
	return (buffer);
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
extern char **environ;
/**
 * path_handler - path handler
 * @file_name: name of file
 *
 * @path: path
 *
 * return: file_name
 */
int path_handler(char *buffer)
{
	int status = 0;
	pid_t pid = fork();
	if (pid == 0)
	{
		char *argv[64];
		line_devider(buffer, argv);
		if (argv[0] == NULL)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(argv[0], "env") == 0)
		{
			char **env = environ;

			while (*env != NULL)
			{
				printf("%s\n", *env);
				env++;
			}
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		if (argv[0][0] == '/')
		{
			if (access(argv[0], X_OK) == 0)
			{
				if (execve(argv[0], argv, environ) == -1)
				{
					perror("execve");
					free(buffer);
					exit(EXIT_FAILURE);
				}
			}
		}
		else
		{
			char *path = getenv("PATH");
			char *token;
			if (path == NULL)
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
				free(buffer);
				exit(127);
			}
			token = strtok(path, ":");
			while (token != NULL)
			{
				char executable_path[256];
				snprintf(executable_path, sizeof(executable_path), "%s/%s", token, argv[0]);
				if (access(executable_path, X_OK) == 0)
				{
					if (execve(executable_path, argv, environ) == -1)
					{
						perror("execve");
						free(buffer);
						exit(EXIT_FAILURE);
					}
				}
				token = strtok(NULL, ":");
			}
		}
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		free(buffer);
		exit(127);
	}
	else if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("ERROR");
		}
		free(buffer);
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
		}
		else 
			status = 1;
	}
	else if (pid == -1)
	{
		perror("fork");
                free(buffer);
                exit(EXIT_FAILURE);
	}
	return (status);
}
/**
 * main - main func
 *
 * Return: int
 */
int main(void)
{
	char *buffer = NULL;
	int status = 0;
	while (1)
	{
		buffer = get_input();
		if (buffer == NULL)
			break;
		if (strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			exit(0);
		}
		status = path_handler(buffer);
		if (status == 2)
		{
			exit(2);
		}
	}
	return (status);
}
