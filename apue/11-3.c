#include "apue.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    sleep(3);
    pthread_exit((void *)2);
}

int main(void)
{
    int       err;
    pthread_t tid1, tid2;
    void *    tret;
    err = pthread_create(&tid1, NULL, thr_fn1, NULL);

    if(err != 0)
        err_exit(err, "can't creat thread 1");

    err = pthread_create(&tid2, NULL, thr_fn2, NULL);

    if(err != 0)
        err_exit(err, "can't creat thread 2");

    // pthread_join, 等待线程的结束, 不然主线程很快执行完成，新创建的线程还没有执行就结束了
    err = pthread_join(tid1, &tret);
    if(err != 0)
        err_exit(err, "can't join with thread 1");
    printf("thread exit code %ld\n", (long)tret);

    err = pthread_join(tid2, &tret);
    if(err != 0)
        err_exit(err, "can't join with thread 2");
    printf("thread exit code %ld\n", (long)tret);

    return 0;
}
