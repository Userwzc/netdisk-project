#include <func.h>


void* thread_func(void *p)
{
    void *p1=malloc(20);
    printf("I am child thread,start free\n");
    sleep(1);
    free(p1);
    printf("free success\n");
    return (void*)0;
}
//子线程被cancel，malloc的空间没有得到释放
int main()
{
    pthread_t th_id;
    int ret=pthread_create(&th_id,NULL,thread_func,NULL);//创建线程
    THREAD_ERR_CHECK(ret,"pthread_create");
    printf("I am main thread\n");
    //取消子线程
    ret=pthread_cancel(th_id);
    THREAD_ERR_CHECK(ret,"pthread_cancel");
    long thread_ret;//用来接子线程的返回值
    ret=pthread_join(th_id,(void**)&thread_ret);//类似于wait
    THREAD_ERR_CHECK(ret,"pthread_join");
    printf("I am main thread %ld\n",thread_ret);//子线程被cancel成功返回值是-1
    return 0;
}