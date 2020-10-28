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
    int                socket_server, socket_client;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int                err;
    unsigned char      rx_buffer[2048];

    socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_server < 0)
    {
        printf("socket error\n");
        return -1;
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port        = htons(PORT);

    err = bind(socket_server, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(err < 0)
    {
        printf("errno = %d\n", errno);
        printf("bind error\n");
        return -1;
    }

    err = listen(socket_server, BACKLOG);
    if(err < 0)
    {
        printf("listen error\n");
        return -1;
    }

    while(1)
    {
        socklen_t addrlen = sizeof(struct sockaddr);

        socket_client = accept(socket_server, (struct sockaddr *)&client_addr, &addrlen);
        if(socket_client < 0)
        {
            printf("continue to try\n");
            continue;
        }
        printf("One tcp client has connected");

        while(1)
        {
            int len = recv(socket_client, rx_buffer, sizeof(rx_buffer) - 1, 0);
            if(len < 0)
            {
                shutdown(socket_client, 0);
                close(socket_client);
                break;
            }
            else if(len == 0)  //Connection closed
            {
                shutdown(socket_client, 0);
                close(socket_client);
                break;
            }
            else
            {
                // process the data received
                printf("%s", rx_buffer);
            }
        }
    }

    return 0;
}
