#include <func.h>
void cleanup1(void *p)
{
    printf("I am child thread,start free\n");
    free(p);
    printf("free success\n");
}

void* thread_func(void *p)
{
    void *p1=malloc(20);
    pthread_cleanup_push(cleanup1,p1);//把cleanup1放入清理函数栈
    sleep(1);
    printf("I am child,正常退出\n");
    pthread_cleanup_pop(1);//弹出清理函数并执行
    return (void*)0;
}
//子线程被cancel，通过cleanup清理函数，来free对应的空间
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