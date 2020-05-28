#include "apue.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void sig_usr(int);

int main(void)
{
    if(signal(SIGUSR1, sig_usr) == SIG_ERR)
        puts("can't catch SIGUSR1");

    if(signal(SIGUSR2, sig_usr) == SIG_ERR)
        puts("can't catch SIGUSR2");
    for(;;)
        pause();
    return 0;
}

static void sig_usr(int signo)
{
    if(signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if(signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else
        printf("received signal %d\n", signo);
}
