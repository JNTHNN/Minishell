// #include "./includes/minishell.h"

// int main (int a, char **b, char **c)
// {
//     char *pos;
// 	char *old_pos;

// 	pos = getenv("PWD");
// 	old_pos = getenv("OLD_PWD");
// 	printf("PWD [%s] | OLD_PWD [%s]\n", pos, old_pos);
// 	if (chdir(b[1]) == -1)
// 		perror("chdir()");
// 	printf("CD EXECUTE WITH DIRECTORY [%s] ---\n", b[1]);
// 	pos = getenv("PWD");
// 	old_pos = getenv("OLD_PWD");
// 	printf("PWD [%s] | OLD_PWD [%s]\n", pos, old_pos);
// }
#include "./includes/minishell.h"

int main (int a, char **b, char **c)
{
    char *pos;
    char *old_pos;
    char cwd[1024];

    pos = getenv("PWD");
    old_pos = getenv("OLD_PWD");
    printf("PWD [%s] | OLD_PWD [%s]\n", pos, old_pos);
    if (chdir(b[1]) == -1)
        perror("chdir()");
    else
    {
        setenv("OLD_PWD", pos, 1);
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            setenv("PWD", cwd, 1);
    }
    printf("CD EXECUTE WITH DIRECTORY [%s] ---\n", b[1]);
    pos = getenv("PWD");
    old_pos = getenv("OLD_PWD");
    printf("PWD [%s] | OLD_PWD [%s]\n", pos, old_pos);
}