// =============================================================================
//  FileName    :	4-2.c
//  Author      :	author
//  Email       :	email@email.com
//  Description :	复制空洞文件
//                  ./a.out hole_file dest_file
//  Version     :	1.0
//  LastChange  :	2022-10-07 15:12:52
//  ChangeLog   :
// =============================================================================
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "Please enter correct parameters!\n");
        return 0;
    }

    char *hole_file = argv[1];
    char *dest_file = argv[2];

    char buf[BUFSIZ] = {0};

    int in_fd, out_fd;
    if((in_fd = open(hole_file, O_RDONLY)) < 0)
    {
        fprintf(stderr, "Don't exist hole file.\n");
        exit(0);
    }

    if((out_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
    {
        fprintf(stderr, "File creation failed!\n");
        exit(0);
    }

    int read_nums = 0;
    int hole_size = 0;
    while((read_nums = read(in_fd, buf, BUFSIZ)) > 0)
    {
        for(int i = 0; i < read_nums; i++)
        {
            if(buf[i] != 0)
                write(out_fd, &buf[i], 1);
            else
                hole_size++;
        }
        lseek(out_fd, hole_size, SEEK_CUR);
        hole_size = 0;
    }

    close(in_fd);
    close(out_fd);

    return 0;
}
