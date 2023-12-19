#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHAR_BUFFER 1024
int main(void)
{
        char *buffer;
        size_t len = 1024, read;
        buffer = malloc(len);
        char *token;
        if (buffer == NULL)
                return (0);
        while (1)
        {
                printf("$ ");
                read = getline(&buffer, &len, stdin);
                if (read == -1)
                        break;
                token = strtok(buffer," ");
                while (token)
                {
                        printf("%s\n", token);
                        token = strtok(NULL," ");
                }
        }
        return (0);
}
