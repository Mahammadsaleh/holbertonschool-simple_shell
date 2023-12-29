#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#define CHAR_BUFFER 1024
extern char **environ;
/**
 * line_devider - devide the line
 * @buffer: string
 *
 * Return: char ptr to ptr
 */
char **line_divider(char *buffer, char **arr)
{
		char *token;
	int i = 0;

	token = strtok(buffer, " \n\t");
	while (token && i < 63)
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
 * path_handler - path handler
 * @file_name: name of file
 *
 * @path: path
 *
 * return: file_name
 */
int execute(char *buffer)
{
	int status = 0;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("ERROR");
		free(buffer);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *arr[100];
		line_divider(buffer, arr);
		if (arr[0] == NULL)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(arr[0], "env") == 0)
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
		if (strchr(arr[0], '/') != NULL)
		{
			if (access(arr[0], X_OK) == 0)
			{
				if (execve(arr[0], arr, environ) == -1)
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
				char error_message[CHAR_BUFFER];
				snprintf(error_message, sizeof(error_message), "./hsh: 1: %s: not found\n", arr[0]);
				write(STDERR_FILENO, error_message, strlen(error_message));
				free(buffer);
				exit(127);
			}
			token = strtok(path, ":");
			while (token)
			{
				char cmd[100];
				snprintf(cmd, sizeof(cmd), "%s/%s", token, arr[0]);
				if (access(cmd, X_OK) == 0)
				{
					if (execve(cmd, arr, environ) == -1)
					{
						perror("execve");
						free(buffer);
						exit(EXIT_FAILURE);
					}
				}
				token = strtok(NULL, ":");
			}
		}
		fprintf(stderr, "./hsh: 1: %s: not found\n", arr[0]);
		free(buffer);
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(buffer);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
			status = 1;
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
	char *buffer;
	int status;
	
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		buffer = get_input();
		if (buffer == NULL)
			break;
		if (strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			exit(0);
		}
		status = execute(buffer);
		if (status == 2 && isatty(STDIN_FILENO))
		{
			exit(2);
		}
	}
	return (status);
}
