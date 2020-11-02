#include <netinet/in.h>
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

int main(int argc, char *argv[])
{
    int  err;
    char rx_buffer[2048];

    int socket_fd, connected_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        printf("socket error\n");
        return -1;
    }

    struct sockaddr_in server_addr, client_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port        = htons(PORT);

    if(bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("errno = %d\n", errno);
        printf("bind error\n");
        return -1;
    }

    if(listen(socket_fd, BACKLOG) < 0)
    {
        printf("listen error\n");
        return -1;
    }

    socklen_t addrlen = sizeof(struct sockaddr);
    while(1)
    {
        connected_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &addrlen);
        if(connected_fd < 0)
        {
            printf("continue to try\n");
            continue;
        }
        printf("connection from %s, port %d\n", inet_ntop(AF_INET, &client_addr.sin_addr, rx_buffer, sizeof(rx_buffer)), ntohs(client_addr.sin_port));

        while(1)
        {
            memset(rx_buffer, 0, sizeof(rx_buffer));
            int len = read(connected_fd, rx_buffer, sizeof(rx_buffer) - 1);
            printf("%s", rx_buffer);

            sprintf(rx_buffer, "%d bytes received\n", len);
            write(connected_fd, rx_buffer, strlen(rx_buffer) + 1);
        }
    }

    return 0;
}
