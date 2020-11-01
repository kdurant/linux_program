#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define PORT 8888
#define BACKLOG 2
#define BUF_SIZE 2048
unsigned char rx_buffer[BUF_SIZE];

void *socket_process(void *data)
{
    // 分离线程, 线程结束后会自动释放资源
    pthread_detach(pthread_self());

    int new_client_fd = (int)data;

    while(1)
    {
        int length = recv(new_client_fd, rx_buffer, BUF_SIZE, 0);
        if(length < 0)
        {
            perror("accept failed.\n");
            exit(1);
        }

        send(new_client_fd, rx_buffer, length, 0);
        memset(rx_buffer, 0, BUF_SIZE);
    }
}

int main(int argc, char *argv[])
{
    int err;

    int socket_server;
    socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_server < 0)
    {
        printf("socket error\n");
        return -1;
    }

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port        = htons(PORT);

    if(bind(socket_server, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("errno = %d\n", errno);
        printf("bind error\n");
        return -1;
    }

    if(listen(socket_server, BACKLOG) < 0)
    {
        printf("listen error\n");
        return -1;
    }

    while(1)
    {
        struct sockaddr_in client_addr;
        socklen_t          addrlen       = sizeof(struct sockaddr);
        int                new_client_fd = accept(socket_server, (struct sockaddr *)&client_addr, &addrlen);
        if(new_client_fd < 0)
        {
            printf("continue to try\n");
            continue;
        }
        printf("One tcp client has connected\n");
        printf("IP is %s\n", inet_ntoa(client_addr.sin_addr));
        printf("Port is %d\n", htons(client_addr.sin_port));

        void *    threadReturn;
        pthread_t child_thread;
        if(pthread_create(&child_thread, NULL, socket_process, (void *)new_client_fd) < 0)
        {
            printf("pthread_create failed : %s\n", strerror(errno));
        }
    }
    close(socket_server);
    return 0;
}

