/*=============================================================================
# FileName    :	t_write.c
# Author      :	author
# Email       :	email@email.com
# Description : read data from argv[1], set to iov array	
# Version     :	1.0
# LastChange  :	2019-12-03 18:32:18
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

int main(int argc, char *argv[])
{
    int          fd;
    struct iovec iov[3];
    struct stat  myStruct;
    int          x;

#define STR_SIZE 100
    char    str[STR_SIZE];
    ssize_t numWrite, totRequired;
    char *  s1 = "durant\n";
    char *  s2 = "james\n";
    char *  s3 = "kobe\n";

    if(argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    fd = open(argv[1], O_RDWR);
    if(fd == -1)
        errExit("open");
    iov[0].iov_base = s1;
    iov[0].iov_len  = strlen(s1);
    totRequired += iov[0].iov_len;

    iov[1].iov_base = s2;
    iov[1].iov_len  = strlen(s2);
    totRequired += iov[1].iov_len;

    iov[2].iov_base = s3;
    iov[2].iov_len  = strlen(s3);
    totRequired += iov[2].iov_len;

    numWrite = writev(fd, iov, 3);
    if(numWrite == -1)
        errExit("readv");

    if(numWrite < totRequired)
        printf("Write fewer bytes than requested\n");

    printf("totol bytes requested: %ld; bytes read: %ld\n", (long)totRequired, (long)numWrite);
    exit(EXIT_SUCCESS);
}
