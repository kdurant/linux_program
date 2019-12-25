/*=============================================================================
# FileName    :	t_readv.c
# Author      :	author
# Email       :	email@email.com
# Description : read data from argv[1], set to iov array	
# Version     :	1.0
# LastChange  :	2019-12-03 18:28:22
# ChangeLog   :	
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "error_functions.h"
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
    int          fd;
    struct iovec iov[3];
    struct stat  myStruct;
    int          x;

#define STR_SIZE 100
    char    str[STR_SIZE];
    ssize_t numRead, totRequired;

    if(argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    fd = open(argv[1], O_RDONLY);
    if(fd == -1)
        errExit("open");
    totRequired     = 0;
    iov[0].iov_base = &myStruct;
    iov[0].iov_len  = sizeof(struct stat);
    totRequired += iov[0].iov_len;

    iov[1].iov_base = &x;
    iov[1].iov_len  = sizeof(x);
    totRequired += iov[1].iov_len;

    iov[2].iov_base = str;
    iov[2].iov_len  = STR_SIZE;
    totRequired += iov[2].iov_len;

    numRead = readv(fd, iov, 3);
    if(numRead == -1)
        errExit("readv");

    if(numRead < totRequired)
        printf("Read fewer bytes than requested\n");

    printf("totol bytes requested: %ld; bytes read: %ld\n", (long)totRequired, (long)numRead);
    exit(EXIT_SUCCESS);
}
