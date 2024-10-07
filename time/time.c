#include <time.h>
#include <stdio.h>


// typedef __time_t time_t;

// 获取自纪元（1970 年 1 月 1 日 00:00:00 UTC）以来经过的秒数


int main()
{
    time_t t;
    time(&t);

    printf("%ld\n", t);  // 1630826068
}
