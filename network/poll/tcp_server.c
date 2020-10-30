#include <asm-generic/errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/poll.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <errno.h>

#define OPEN_MAX (100)
#define PORT (8888)

int main(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in my_addr;
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family      = AF_INET;
    my_addr.sin_port        = htons(PORT);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));

    listen(sockfd, 10);

    struct pollfd client[OPEN_MAX];
    int           i    = 0;
    int           maxi = 0;
    for(; i < OPEN_MAX; i++)
        client[i].fd = 0;
    client[0].fd     = sockfd;  // 需要检测的描述符
    client[0].events = POLLIN;  // 普通或优先级带数据可读

    while(1)
    {
        int ret = poll(client, maxi + 1, -1);

        // 检测sockfd是否存在连接
        if((client[0].revents && POLLIN) == POLLIN)
        {
            struct sockaddr_in cli_addr;
            int                clilen = sizeof(cli_addr);
            int                connfd = 0;

            // 从tcp完成连接中提取客户端
            connfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

            // 将提取到的connfd放入到poll结构体数组中，以便poll函数检测
            for(i = 0; i < OPEN_MAX; i++)
            {
                if(client[i].fd < 0)
                {
                    client[i].fd     = connfd;
                    client[i].events = POLLIN;
                    break;
                }
            }
            if(i > maxi)
                maxi = i;

            if(--ret <= 0)
                continue;
        }

        for(i = 0; i <= maxi; i++)
        {
            if(client[i].fd < 0)
                continue;

            if(client[i].revents & (POLLIN | POLLERR))
            {
                int  len      = 0;
                char buf[128] = "";

                // 接收客户端数据
                if((len = recv(client[i].fd, buf, sizeof(buf), 0)) < 0)
                {
                    if(errno == ECONNRESET)  // TCP连接超时，RST
                    {
                        close(client[i].fd);
                        client[i].fd = -1;
                    }
                    else
                        perror("read error:");
                }
                else if(len == 0)  // 客户端关闭连接
                {
                    close(client[i].fd);
                    client[i].fd = -1;
                }
                else  // 处理接收到客户端的数据
                    send(client[i].fd, buf, len, 0);
            }
        }

        return 0;
    }
}
