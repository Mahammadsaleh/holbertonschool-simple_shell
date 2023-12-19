#include <stdio.h>
#include <stdlib.h>
#define CHAR_BUFFER 1024
int main(void)
{
	char *buffer;
	size_t len = 1024, read;
	buffer = malloc(len);
	if (buffer == NULL)
		return (0);
	while (1)
	{
		printf("$ ");
		read = getline(&buffer, &len, stdin);
		if (read == -1)
			break;
		printf("%s", buffer);
	}
	return (0);
}
