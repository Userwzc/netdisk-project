#include <func.h>

typedef struct{
    int val;
    pthread_mutex_t mutex;
}Share_t,*pShare_t;


void* thread_func(void *p)
{
    pthread_mutex_lock(&((pShare_t)p)->mutex);//加锁
    printf("I am child thread,lock 成功\n");
    // pthread_mutex_unlock(&((pShare_t)p)->mutex);//解锁
    return NULL;
}

int main()
{
    Share_t t;
    int ret;
    ret=pthread_mutex_init(&t.mutex,NULL);
    THREAD_ERR_CHECK(ret,"pthread_mutex_init");
    pthread_t pth_id;
    pthread_create(&pth_id,NULL,thread_func,&t);
    sleep(1);
    printf("main start unlock\n");
    pthread_mutex_unlock(&t.mutex);//主线程解锁
    pthread_join(pth_id,NULL);
    printf("main thread\n");
    return 0;
}