#include "apue.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(void)
{
    int             err;
    struct timespec tout;
    struct tm*      temp;
    char            buf[64];

    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&lock);
    printf("mutex is locked\n");
    clock_gettime(CLOCK_REALTIME, &tout);
    temp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", temp);
    printf("current time is %s\n", buf);
    tout.tv_sec += 10;
    err = pthread_mutex_timedlock(&lock, &tout);

    clock_gettime(CLOCK_REALTIME, &tout);
    temp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", temp);
    printf("current time is %s\n", buf);

    if(err == 0)
        printf("mutex locked again!\n");
    else
        printf("can't lock mvtex again: %s \n", strerror(err));

    return 0;
}
