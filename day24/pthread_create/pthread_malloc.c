#include <func.h>

//子线程如何接收参数
void* thread_func(void *p)
{
    printf("I am child thread,%s\n",(char*)p);
    strcpy(p,"world");//子线程把对应空间内容改为world
    return NULL;
}

int main()
{
    pthread_t th_id;
    char *pHeap=(char*)malloc(20);
    strcpy(pHeap,"hello");//申请一块堆空间，里边放hello
    int ret=pthread_create(&th_id,NULL,thread_func,pHeap);//创建线程
    THREAD_ERR_CHECK(ret,"pthread_create");
    printf("I am main thread \n");
    pthread_join(th_id,NULL);//类似于wait
    printf("parent thread, %s\n",pHeap);//主线程就输出了world
    free(pHeap);
    return 0;
}