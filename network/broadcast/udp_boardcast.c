// https://www.cnblogs.com/kele-dad/p/10513272.html
// usage: ./a.out 127.0.0.1 8888
#include <asm-generic/socket.h>
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

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        fprintf(stderr, "usage: %s is port\n", argv[0]);
        exit(1);
    }

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(socket_fd < 0)
    {
        perror("socket error");
        exit(1);
    }

    int opt = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    printf("I will broadcast...\n");
    char *  info = "hello world";
    ssize_t size = strlen(info) * sizeof(char);
    if(sendto(socket_fd, info, size, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("sendto error");
        exit(1);
    }
    else
        printf("broadcast success\n");

    close(socket_fd);

    return 0;
}
