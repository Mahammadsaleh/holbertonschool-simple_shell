#include <stdio.h>
#include <stddef.h>
int main(int ac, char **av)
{
	int i = 1;
	while (av[i] != NULL)
	{
		printf("%s", av[i]);
		i++;
	}
	printf("\n");
	return (0);
}
