#include <cstddef>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/poll.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <errno.h>

#define ECHO_SERVER_PORT (8888)
#define LISTEN_BACKLOG (16)
#define MAX_EVENT_COUNT (32)
#define BUF_SIZE 2048

int main(void)
{
    int           ret;
    unsigned char buf[BUF_SIZE];

    int server_fd, client_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0)
    {
        printf("socket error\n");
        return -1;
    }

    struct sockaddr_in server_addr, client_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port        = htons(ECHO_SERVER_PORT);

    if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("errno = %d\n", errno);
        printf("bind error\n");
        return -1;
    }

    if(listen(server_fd, LISTEN_BACKLOG) < 0)
    {
        printf("listen error\n");
        return -1;
    }

    int epoll_fd = epoll_create(1);
    if(epoll_fd == -1)
    {
        perror("epoll create failed.\n");
        exit(1);
    }
    struct epoll_event event;
    event.events  = EPOLLIN;
    event.data.fd = server_fd;
    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1)
    {
        perror("epoll_ctl failed.\n");
        exit(1);
    }

    struct epoll_event *event_array = (struct epoll_event *)malloc(sizeof(struct epoll_event) * MAX_EVENT_COUNT);

    int       ready_count;
    socklen_t addr_len = sizeof(struct sockaddr);

    while(1)
    {
        ready_count = epoll_wait(epoll_fd, event_array, MAX_EVENT_COUNT, -1);
        if(ready_count == -1)
        {
            perror("epoll_wait failed.\n");
            exit(1);
        }

        for(int i = 0; i < ready_count; i++)
        {
            if(event_array[i].data.fd == server_fd)
            {
                client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
                if(client_fd == -1)
                {
                    perror("accept failed.\n");
                    exit(1);
                }
                event.events  = EPOLLIN;
                event.data.fd = client_fd;

                if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) == -1)
                {
                    perror("epoll_ctl failed.\n");
                    exit(1);
                }
            }
            else
            {
                ret = recv(event_array[i].data.fd, buf, BUF_SIZE, 0);
                if(ret <= 0)
                {
                    close(event_array[i].data.fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, event_array[i].data.fd, &event);
                    continue;
                }
                else
                {
                    if(send(event_array[i].data.fd, buf, (size_t)ret, 0) == -1)
                        perror("send failed.\n");
                }
            }
        }
    }
    close(epoll_fd);
    close(server_fd);
    free(event_array);

    return 0;
}
