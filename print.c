#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("\r\033[2K");
    fflush(stdout);
    sleep(1); // Attendre pour que l'utilisateur puisse voir l'effet
    printf("TEST 1");
    printf("TEST 3");
}