#include <func.h>

void* thread_func(void *p1)
{
    printf("I am child thread\n");
    time_t now=time(NULL);//获取当前时间，距离1970年1月1号的秒数
    char mytime[100];
    char *p=ctime_r(&now,mytime);//变为字符串
    printf("I am child %s\n",mytime);
    sleep(5);
    printf("I am child twice %s\n",mytime);
    return NULL;
}

int main()
{
    pthread_t th_id;
    int ret=pthread_create(&th_id,NULL,thread_func,NULL);//创建线程
    THREAD_ERR_CHECK(ret,"pthread_create");
    sleep(2);
    time_t now=time(NULL);//获取当前时间，距离1970年1月1号的秒数
    char mytime[100];
    char *p=ctime_r(&now,mytime);//变为字符串
    printf("I am main thread %s\n",p);
    pthread_join(th_id,NULL);//类似于wait
    return 0;
}