#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int fd[2];
    int pid1;

    if (pipe(fd) == -1)
        return (1);
    pid1 = fork();
    if (pid1 < 0)
        return (2);
    if (pid1 == 0)
    {
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
    }
    waitpid(pid1, NULL, 0);
    return (0);
}