#include <func.h>
void cleanup1(void *p)
{
    printf("I am child thread,%ld\n",(long)p);
}

void* thread_func(void *p)
{
    pthread_cleanup_push(cleanup1,(void*)1);//把cleanup1放入清理函数栈
    pthread_cleanup_push(cleanup1,(void*)2);
    printf("I am child,正常退出\n");
    pthread_exit(NULL);
    pthread_cleanup_pop(1);//弹出清理函数并执行
    pthread_cleanup_pop(1);//弹出清理函数并执行
}
//子线程清理函数执行顺序
int main()
{
    pthread_t th_id;
    int ret=pthread_create(&th_id,NULL,thread_func,NULL);//创建线程
    THREAD_ERR_CHECK(ret,"pthread_create");
    printf("I am main thread\n");

    long thread_ret;//用来接子线程的返回值
    ret=pthread_join(th_id,(void**)&thread_ret);//类似于wait
    THREAD_ERR_CHECK(ret,"pthread_join");
    printf("I am main thread %ld\n",thread_ret);//子线程被cancel成功返回值是-1
    return 0;
}