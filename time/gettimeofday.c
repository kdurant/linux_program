#include <stdio.h>
#include <sys/time.h>


/*
struct timeval {
    time_t tv_sec; // seconds 
    long tv_usec; // microseconds 
};
*/

int main() {
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1) {
        perror("gettimeofday");
        return 1;
    }

    printf("当前时间：%ld 秒，%ld 微秒\n", tv.tv_sec, tv.tv_usec);

    return 0;
}