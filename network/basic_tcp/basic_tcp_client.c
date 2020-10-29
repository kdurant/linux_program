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
    int                socket_client;
    int                size;
    unsigned char      tx_buffer[2048];
    socket_client = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_client < 0)
    {
        perror("socket");
        return -1;
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* IP地址 */
    //server_addr.sin_addr.s_addr = htonl("127.0.0.1");
    inet_aton("127.0.0.1", &(server_addr.sin_addr));

    err = connect(socket_client, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(err < 0)
    {
        printf("connection failed\n");
        exit(1);
    }
    printf("success in connecting tcp server\n");

    while(1)
    {
        memset(tx_buffer, 0, sizeof(tx_buffer));
        size = read(0, tx_buffer, 1024);  // 从标准输入中读取数据
        if(size > 0)
        {
            write(socket_client, tx_buffer, size);
            size = read(socket_client, tx_buffer, 1024);  // 从服务器读取数据
            write(1, tx_buffer, size);                    // 写到标准输出
        }
    }

    return 0;
}
