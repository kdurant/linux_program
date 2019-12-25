#include <unistd.h>
#include <stdio.h>

int main(void)
{
    pid_t fpid;
    int   count = 0;

    fpid = fork();

    if(fpid < 0)
        printf("error in fork!\n");
    else if(fpid == 0)
    {
        printf("I am the child process, my id is %d\n", getpid());
        count++;
    }
    else
    {
        printf("I am the parent process, my id is %d\n", getpid());
        count++;
    }
    printf("result is : %d\n", count);

    return 0;
}
