#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
    char *test;

    test = malloc(-1);
    printf("ERRNO [%d]\n", errno);
    return (perror("test"));
}