#include <func.h>

void *thread_func(void *p)
{
    while(1)
    {
        pthread_testcancel(); //检查取消标志位
    }
    return (void*)0;
}
//子线程退出，接一个整型

int main()
{
    pthread_t th_id;
    int ret = pthread_create(&th_id,NULL,thread_func,NULL);
    THREAD_ERR_CHECK(ret,"pthread_create");
    printf("I am main thread\n");
    //取消子线程
    ret=pthread_cancel(th_id);
    THREAD_ERR_CHECK(ret,"pthread_cancel");
    long thread_ret;
    ret=pthread_join(th_id,(void**)&thread_ret);
    THREAD_ERR_CHECK(ret,"pthread_join");
    printf("I am main thread %ld\n",thread_ret);
    return 0;
}