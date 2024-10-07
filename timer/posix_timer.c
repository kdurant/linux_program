#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void timer_handler(int signum)
{
    time_t current_time;
    struct tm *time_info;
    time_info = localtime(&current_time);

    printf("%d:%d:%d, Timer expired\n", time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
}   

int main()
{
    struct sigaction sa;
    struct itimerspec its;
    timer_t timerid;

    sa.sa_handler = timer_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGALRM, &sa, NULL) == -1) 
    {
        perror("sigaction");
        return 1;
    }

    if(timer_create(CLOCK_REALTIME, NULL, &timerid) == -1)
    {
        perror("timer_create");
        return 1;
    }
    
    its.it_value.tv_sec = 1;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 1;
    its.it_interval.tv_nsec = 0;

    if(timer_settime(timerid, 0, &its, NULL) == -1)
    {
        perror("timer_settime");
        return 1;
    }

    while(1)
    {}

    return 0;

}