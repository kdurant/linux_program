#include <asm-generic/errno-base.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include "error_functions.h"
#include "get_num.h"
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int s, sig;

    if(argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s sig-num pid\n", argv[0]);

    sig = getInt(argv[2], 0, "sig-num");

    s = kill(getLong(argv[1], 0, "pid"), sig);

    if(sig != 0)
    {
        if(s == -1)
            errExit("kill");
    }
    else
    {
        if(s == 0)
            printf("Process exists and we can send it a signal\n");
        else
        {
            if(errno == EPERM)
                printf("Process exists, but we don't have permission to send it a signal\n");
            else if(errno == ESRCH)
            {
                printf("Process does not exist\n");
            }
            else
                errExit("kill");
        }
    }
    return 0;
}
