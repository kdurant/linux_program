#include "error_functions.h"
#include "tlpi_hdr.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static int idata = 111;

int main(int argc, char *argv[])
{
    int istack = 222;

    pid_t childPid;

    switch(childPid = fork())
    {
        case -1:
            errExit("fork");
            break;
        case 0:
            idata *= 3;
            istack *= 3;
            break;
        default:
            sleep(3);
            break;
    }

    printf("PID=%ld %s idata=%d istack=%d\n", (long)getpid(), (childPid == 0) ? "(child) " : "(parent)", idata, istack);

    exit(EXIT_SUCCESS);
}
