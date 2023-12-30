#include "main.h"
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
