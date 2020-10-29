#include <asm-generic/socket.h>
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT (8100)
#define MAXCLINE (5)
#define BUF_SIZE (200)

int fd[MAXCLINE];
int conn_amount;

void showclient()
{
    printf("clent amount: %d\n", conn_amount);
    for(int i = 0; i < MAXCLINE; i++)
    {
        printf("[%d]:%d", i, fd[i]);
    }
    printf("\n");
}

int main(void)
{
    int                sock_fd, new_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t          sin_size;

    int  yes = 1;
    char buf[BUF_SIZE];
    int  ret;
    int  i;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0)
    {
        perror("setsockopt");
        exit(1);
    }
    printf("sock_fd = %d\n", sock_fd);

    if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("setsockopt error\n");
        exit(1);
    }

    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(MYPORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&server_addr.sin_addr, '\0', sizeof(server_addr.sin_addr));
    if(bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind error\n");
        exit(1);
    }

    if(listen(sock_fd, MAXCLINE) == -1)
    {
        perror("listen error\n");
        exit(1);
    }
    printf("listen port %d\n", MYPORT);

    fd_set         fdsr;
    int            maxsock;
    struct timeval tv;
    conn_amount = 0;
    sin_size    = sizeof(client_addr);
    maxsock     = sock_fd;

    while(1)
    {
        FD_ZERO(&fdsr);
        FD_SET(sock_fd, &fdsr);
        tv.tv_sec  = 30;
        tv.tv_usec = 0;

        for(i = 0; i < MAXCLINE; i++)
        {
            if(fd[i] != 0)
            {
                FD_SET(fd[i], &fdsr);
            }
        }

        ret = select(maxsock + 1, &fdsr, NULL, NULL, &tv);
        if(ret < 0)
        {
            perror("select error!\n");
            break;
        }
        else if(ret == 0)
        {
            printf("timeout\n");
            continue;
        }
    }

    return 0;
}
