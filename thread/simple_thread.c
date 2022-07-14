#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void *threadFunc(void *arg)
{
    printf("sub-thread id : %lx\n", pthread_self());
    char *s = (char *)arg;
    printf("%s", s);
    return (void *)strlen(s);
}

int main(int argc, char *argv[])
{
    pthread_t t1;
    void     *res;
    int       s;

    s = pthread_create(&t1, NULL, threadFunc, "Hello world from sub-thread\n");
    if(s != 0)
        printf("pthread create successfully\n");

    printf("Hello world from main()\n");
    s = pthread_join(t1, &res);

    if(s != 0)
    {
        printf("calling pthread wait for termination of the thread [t1]\n");
    }

    exit(EXIT_SUCCESS);
}
