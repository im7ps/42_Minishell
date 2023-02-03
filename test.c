#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
    char **env;
    int i;

    for (env = envp; *env != 0; env++)
    {
        printf("%s\n", *env);
    }

    return 0;
}
