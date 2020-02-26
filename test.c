#include "unistd.h"

int main(int argc, char const *argv[], char **env)
{
    char *path = "./minishell";
    int x = execve(path, argv, env);
    printf("status: %d\n", x);
    return 0;
}
