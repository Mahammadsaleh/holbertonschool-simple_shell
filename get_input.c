#include "main.h"
/**
 * get_input - input part
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
