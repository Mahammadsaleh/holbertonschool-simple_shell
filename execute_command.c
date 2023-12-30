#include "main.h"
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * execute_command - execute the path or command that given
 * @buffer: buffer (input from shell)
 * @argv: arguments array
 *
 * Return: status
 */
void execute_command(char *buffer, char **argv)
{
	if (execve(buffer, argv, environ) == -1)
	{
		perror("execve");
		free(buffer);
		exit(EXIT_FAILURE);
	}
}
