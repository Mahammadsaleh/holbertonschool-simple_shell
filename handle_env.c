#include "main.h"
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * handle_env - handle the first argv element was a env
 * @buffer: buffer (input from shell)
 *
 * Return: status
 */
void handle_env(char *buffer)
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
