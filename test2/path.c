#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100
#define MAX_PATH_LENGTH 100

void parseAndExecute(char *input) {
    char *path = getenv("PATH");
    char *token, *fullPath;
    char command[MAX_INPUT_LENGTH];

    strcpy(command, input);

    token = strtok(path, ":");
    while (token != NULL) {
        fullPath = malloc(strlen(token) + strlen(command) + 2); // +2 for / and null terminator
        if (fullPath == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            return;
        }

        sprintf(fullPath, "%s/%s", token, command);
        if (access(fullPath, X_OK) == 0) { // Check if the command exists and is executable
            if (fork() == 0) {
                execl(fullPath, command, NULL);
                fprintf(stderr, "Failed to execute command\n");
                exit(EXIT_FAILURE);
            } else {
                wait(NULL);
                return;
            }
        }

        free(fullPath);
        token = strtok(NULL, ":");
    }

    printf("%s: command not found\n", command);
}

int main() {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        printf(":) ");
        fgets(input, MAX_INPUT_LENGTH, stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline character

        if (strcmp(input, "exit") == 0) {
            break;
        }

        parseAndExecute(input);
    }

    return 0;
}


