#include <func.h>

void* thread_func(void *p)
{
    printf("I am child thread,%lu\n",pthread_self());
    return NULL;
}
//设置线程属性为 不可join
int main()
{
    pthread_t th_id;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    //把属性设置为 PTHREAD_CREATE_DETACHED
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    int ret=pthread_create(&th_id,&attr,thread_func,NULL);//创建线程
    THREAD_ERR_CHECK(ret,"pthread_create");
    ret=pthread_join(th_id,NULL);//类似于wait
    THREAD_ERR_CHECK(ret,"pthread_join");
    return 0;
}