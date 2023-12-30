#include "main.h"
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
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
		if (strchr(argv[0], '/') != NULL)
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
