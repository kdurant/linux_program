#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define PORT 8888

int main(void)
{
    struct sockaddr_in server_addr;
    int                err;
    int                s;
    int                size;
    unsigned char      tx_buffer[2048];

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    //server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_addr.s_addr = htonl("127.0.0.1");
    server_addr.sin_port        = htons(PORT);

    err = connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(err < 0)
    {
        printf("connection failed\n");
        exit(1);
    }

    while(1)
    {
        memcpy(tx_buffer, "hello world", strlen("hello world"));
        send(s, tx_buffer, strlen("hello world"), 0);
        sleep(1);
    }

    return 0;
}
