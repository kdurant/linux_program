/*
如果在获取自旋锁时， 自旋锁处于未锁定状态， 那么将立即获得锁（对自旋锁上锁）；
如果在获取自旋锁时，自旋锁已经处于锁定状态了，那么获取锁操作将会在原地“自旋”， 直到该自旋锁的持有者释放了锁。

由此介绍可知，自旋锁与互斥锁相似， 但是互斥锁在无法获取到锁时会让线程陷入阻塞等待状态；
而自旋锁在无法获取到锁时， 将会在原地“自旋”等待。
“自旋” 其实就是调用者一直在循环查看该自旋锁的持有者是否已经释放了锁，“自旋”一词因此得名。
 */

#include <pthread.h>
#include <stdio.h>

static int glob = 0;

pthread_spinlock_t spin;

void *threadFunction(void *arg)
{
    int loops = *((int *)arg);
    int loc   = 0;
    for(int i = 0; i < loops; i++)
    {
        pthread_spin_lock(&spin);
        loc = glob;
        loc++;
        glob = loc;
        pthread_spin_unlock(&spin);
    }
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    int       loops = 1000000;

    pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE);

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

