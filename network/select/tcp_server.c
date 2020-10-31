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
#include <unistd.h>

#define MYPORT (8888)
#define MAX_CLIENT (5)
#define BUF_SIZE (200)

int fd[MAX_CLIENT];
int conn_amount;

void showclient()
{
    printf("clent amount: %d\n", conn_amount);
    for(int i = 0; i < MAX_CLIENT; i++)
    {
        printf("[%d]:%d\t\t", i, fd[i]);
    }
    printf("\n");
}

int main(void)
{
    int  yes = 1;
    char buf[BUF_SIZE];
    int  ret;
    int  i;

    int sock_fd, new_fd;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0)
    {
        perror("setsockopt");
        exit(1);
    }
    printf("sock_fd = %d\n", sock_fd);

    //设置套接口的选项 SO_REUSEADDR 允许在同一个端口启动服务器的多个实例
    if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("setsockopt error\n");
        exit(1);
    }

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t          sin_size;
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(MYPORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&server_addr.sin_addr, '\0', sizeof(server_addr.sin_addr));
    if(bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind error\n");
        exit(1);
    }

    if(listen(sock_fd, MAX_CLIENT) == -1)
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
        //select()的参数在每次select()函数的返回会被内核修改，所以这里需要重新设置
        FD_ZERO(&fdsr);
        FD_SET(sock_fd, &fdsr);
        tv.tv_sec  = 30;
        tv.tv_usec = 0;

        //将所有的连接全部加到这个这个集合中，可以监测客户端是否有数据到来
        for(i = 0; i < MAX_CLIENT; i++)
        {
            if(fd[i] != 0)
            {
                FD_SET(fd[i], &fdsr);
            }
        }

        // 套接字可读条件
        // 1. socket内核接收缓冲区中字节数>=其低水位标记SO_RCVLOWAT时，此时程序可以无阻塞地读该socket，返回读取到的字节数(>0)
        // 2. socket通信的对端关闭连接，此时对该socket的读操作将返回0表示对端关闭
        // 3. 监听socket上有新的连接请求
        // 4. 套接字上有错误待处理
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

        // 有客户端连接
        for(i = 0; i < conn_amount; i++)
        {
            if(FD_ISSET(fd[i], &fdsr))
            {
                ret = recv(fd[i], buf, sizeof(buf), 0);
                if(ret < 0)
                {
                    printf("client[%d] close\n", i);
                    close(fd[i]);
                    FD_CLR(fd[i], &fdsr);
                    fd[i] = 0;
                    conn_amount--;
                }
                else
                {
                    if(ret < BUF_SIZE)
                        memset(&buf[ret], '\0', 1);
                    printf("client[%d] send:%s", i, buf);
                }
            }
        }

        if(FD_ISSET(sock_fd, &fdsr))
        {
            new_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
            if(new_fd <= 0)
            {
                perror("accept error\n");
                continue;
            }
            printf("One tcp client has connected\n");
            printf("IP is %s\n", inet_ntoa(client_addr.sin_addr));
            printf("Port is %d\n", htons(client_addr.sin_port));

            if(conn_amount < MAX_CLIENT)
            {
                for(i = 0; i < MAX_CLIENT; i++)
                {
                    if(fd[i] == 0)
                    {
                        fd[i] = new_fd;
                        break;
                    }
                }
                conn_amount++;
                printf("new connection cliend[%d]%s:%d\n", conn_amount, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                if(new_fd > maxsock)
                {
                    maxsock = new_fd;  // 有新的的tcp连接进来后，需要更新select的nfds
                }
            }
            else
            {
                printf("max connections arrive, exit\n");
                send(new_fd, "bye", 4, 0);
                close(new_fd);
                continue;
            }
        }
        showclient();
    }

    for(i = 0; i < MAX_CLIENT; i++)
    {
        if(fd[i] != 0)
        {
            close(fd[i]);
        }
    }

    return 0;
}
