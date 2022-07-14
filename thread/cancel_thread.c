#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *threadFunc(void *arg)
{
    int loops = *((int *)arg);
    for(int i = 0; i < loops; i++)
    {
        printf("i = %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main(void)
{
    pthread_t t1;
    int       loop = 10;

    void *res;
    int   status;

    status = pthread_create(&t1, NULL, threadFunc, &loop);
    if(status != 0)
        printf("Thread t1 creation failed\n");
    else
        printf("Thread t1 creation success\n");

    sleep(3);

    status = pthread_cancel(t1);
    if(status != 0)
        printf("Thread t1 cancel failed\n");
    else
        printf("Thread t1 cancel success\n");

    pthread_join(t1, &res);

    return 0;
}
