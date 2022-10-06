/*
tee 命令是从标准输入中读取数据，直至文件结尾，随后将数据写入标准输出和命令行
参数所指定的文件。（44.7 节讨论 FIFO 时，会展示使用 tee 命令的一个例子。）请使用
I/O 系统调用实现 tee 命令。默认情况下，若已存在与命令行参数指定文件同名的文件，
tee 命令会将其覆盖。如文件已存在，请实现-a 命令行选项（tee-a file）在文件结尾处
追加数据。 （请参考附录 B 中对 getopt()函数的描述来解析命令行选项。 ）
*/

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
    int   ch;
    char* filename = NULL;

    printf("argc = %d\n", argc);
    int append = 0;

    if(argc == 1)
        fprintf(stdout, "Need filename\n");
    else if(argc == 2)
    {
        filename = argv[1];
        append   = 0;
    }
    else
    {
        while((ch = getopt(argc, argv, "a:")) != -1)
        {
            switch(ch)
            {
                case 'a':
                    printf("捕获到选项: -a\n");
                    printf("该选项参数为：%s\n\n", optarg);
                    filename = optarg;
                    append   = 1;
                    break;
                case '?':
                    printf("arguments error!\n");
                    return 0;
            }
        }
    }
    int file_flag;
    if(append)
        file_flag = O_RDWR | O_CREAT | O_APPEND;
    else
        file_flag = O_RDWR | O_CREAT;

    int fd = open(filename, file_flag, S_IRUSR | S_IWUSR | S_IROTH | S_IRWXG);
    // int fd = open(filename, O_RDWR);
    if(fd == -1)
    {
        fprintf(stderr, "create file failed!\n");
        return 0;
    }

    char buf[1024];
    int  num = read(0, buf, 1024);
    write(fd, buf, num);
    close(fd);
    return 0;
}
