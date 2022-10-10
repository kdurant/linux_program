#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int food = 0;

/* 静态初始化 一个条件变量 和 一个互斥量*/
pthread_cond_t  has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex       = PTHREAD_MUTEX_INITIALIZER;

void *th_producer(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        printf("--- produce: --------\n");
        food++;
        pthread_mutex_unlock(&mutex);

        pthread_cond_signal(&has_product);  //唤醒线程去消费产品
        sleep(1);
    }
    return NULL;
}

void *th_consumer(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        // 条件变量这个变量其实本身不包含条件信息，
        // 条件的判断不在pthread_cond_wait函数功能中， 而需要外面进行条件判断。
        // 这个条件通常是多个线程或进程的共享变量，
        while(food == 0)
        {
            pthread_cond_wait(&has_product, &mutex);
        }
        food--;
        printf("========= consume: ======\n");
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t pid, cid;
    srand(time(NULL));

    pthread_create(&pid, NULL, th_producer, NULL);
    pthread_create(&cid, NULL, th_consumer, NULL);

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
    return 0;
}

