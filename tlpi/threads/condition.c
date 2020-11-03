#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct msg
{
    struct msg *next;
    int         num;
} msg_t;

msg_t *head = NULL;
msg_t *mp   = NULL;

/* 静态初始化 一个条件变量 和 一个互斥量*/
pthread_cond_t  has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex       = PTHREAD_MUTEX_INITIALIZER;

void *th_producer(void *arg)
{
    while(1)
    {
        mp      = malloc(sizeof(msg_t));
        mp->num = rand() % 1000;  //模拟生产一个产品
        printf("--- produce: %d --------\n", mp->num);

        pthread_mutex_lock(&mutex);
        mp->next = head;
        head     = mp;
        pthread_mutex_unlock(&mutex);

        pthread_cond_signal(&has_product);  //唤醒线程去消费产品
        sleep(rand() % 5);
    }
    return NULL;
}

void *th_consumer(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(head == NULL)
        {  //如果链表里没有产品，就没有抢锁的必要，一直阻塞等待
            pthread_cond_wait(&has_product, &mutex);
        }
        mp   = head;
        head = mp->next;  //模拟消费掉一个产品
        pthread_mutex_unlock(&mutex);

        printf("========= consume: %d ======\n", mp->num);
        free(mp);
        mp = NULL;
        sleep(rand() % 5);
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

