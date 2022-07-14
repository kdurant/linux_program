#include <pthread.h>
#include <stdio.h>

static int glob = 0;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *threadFunction(void *arg)
{
    int loops = *((int *)arg);
    int loc   = 0;
    for(int i = 0; i < loops; i++)
    {
        pthread_mutex_lock(&mtx);
        loc = glob;
        loc++;
        glob = loc;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    int       loops = 1000000;

    int s;
    s = pthread_create(&t1, NULL, threadFunction, &loops);
    if(s != 0)
        printf("Thread t1 creation failed\n");

    s = pthread_create(&t2, NULL, threadFunction, &loops);
    if(s != 0)
        printf("Thread t2 creation failed\n");

    s = pthread_join(t1, NULL);
    s = pthread_join(t2, NULL);

    printf("glob = %d\n", glob);

    return 0;
}

