#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input = readline("Enter the name of the executable: ");
    char *path = getenv("PATH");
    char *path_token;

    if(input == NULL) return 1;
    if(path == NULL) return 1;

    // Split the PATH variable into individual directories
    path_token = strtok(path, ":");
    while (path_token != NULL) {
        char executable_path[1024];
        snprintf(executable_path, sizeof(executable_path), "%s/%s", path_token, input);
        if (access(executable_path, X_OK) == 0) {
            char *args[] = {executable_path, NULL};
            execve(executable_path, args, NULL);
            //we should not reach this point
            printf("execve failed: %s\n", strerror(1));
            return 1;
        }
        path_token = strtok(NULL, ":");
    }
    printf("%s: command not found\n", input);
    free(input);
    return 1;
}
