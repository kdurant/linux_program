#include <sys/timeb.h>
#include <stdio.h>

/*
    struct   timeb{
        time_t   time;                   // 为1970-01-01至今的秒数
        unsigned   short   millitm;      // 千分之一秒即毫秒 
        short   timezonel;               // 为目前时区和Greenwich相差的时间，单位为分钟 
        short   dstflag;                 // 为日光节约时间的修正状态，如果为非0代表启用日光节约时间修正
    };
*/


int main()
{
    struct timeb tp;
    ftime(&tp);
    printf("%ld - %d\n", tp.time, tp.millitm);  // 1630829481 - 995
}
