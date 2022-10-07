// =============================================================================
//  FileName    :	4-2_data.c
//  Author      :	author
//  Email       :	email@email.com
//  Description :	產生一個空洞文件
//  Version     :	1.0
//  LastChange  :	2022-10-07 14:51:14
//  ChangeLog   :
// =============================================================================
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int fd = open("hole.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if(fd == -1)
        fprintf(stdout, "create file failed!\n");
    char *str = "Hello world\n";
    write(fd, str, sizeof(str));

    lseek(fd, 1024 * 1024 + 512, SEEK_CUR);
    write(fd, str, sizeof(str));
    close(fd);

    return 0;
}
