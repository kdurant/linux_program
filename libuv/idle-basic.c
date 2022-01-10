#include <stdint.h>
#include <stdio.h>
#include <uv.h>

int64_t count = 0;
void    wait_for_a_while(uv_idle_t* handle)
{
    count++;

    if(count >= 10e6)
        uv_idle_stop(handle);
}

int main(void)
{
    uv_idle_t idler;
    uv_idle_init(uv_default_loop(), &idler);
    uv_idle_start(&idler, wait_for_a_while);

    printf("Idling...\n");
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    uv_loop_close(uv_default_loop());

    return 0;
}
