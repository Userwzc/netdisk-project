#include <func.h>

//子线程如何接收参数
void* thread_func(void *p)
{
    printf("I am child thread,%ld\n",(long)p);
    return NULL;
}
//传递局部变量的值给子线程
int main()
{
    pthread_t th_id;
    long local=1001;
    int ret=pthread_create(&th_id,NULL,thread_func,(void*)local);//创建线程
    THREAD_ERR_CHECK(ret,"pthread_create");
    local=1002;
    ret=pthread_create(&th_id,NULL,thread_func,(void*)local);//创建线程
    THREAD_ERR_CHECK(ret,"pthread_create");
    printf("I am main thread \n");
    sleep(1);
    return 0;
}