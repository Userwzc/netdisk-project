#include <func.h>

void* thread_func(void *p)
{
    printf("I am child thread\n");
    sleep(1);//为了子线程被cancel成功
    return (void*)0;
}
//子线程退出，我们接一个整型
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