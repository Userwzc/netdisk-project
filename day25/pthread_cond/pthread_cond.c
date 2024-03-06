#include <func.h>
typedef struct{
    // int val;
    pthread_mutex_t mutex;//辅助排队的
    pthread_cond_t cond;
}Share_t,*pShare_t;


void* thread_func(void *p)
{
    pShare_t p1=(pShare_t)p;
    printf("I am child thread\n");
    //任何时候cond_wait之前必须先加锁,由加解锁包裹
    pthread_mutex_lock(&p1->mutex);
    int ret=pthread_cond_wait(&p1->cond,&p1->mutex);
    pthread_mutex_unlock(&p1->mutex);
    printf("I am child thread,I wake\n");
    return (void*)0;
}

//子线程等待在t.cond条件变量上，主线程唤醒
int main()
{
    Share_t t;
    int ret;
    //初始化条件变量，初始化锁
    pthread_mutex_init(&t.mutex,NULL);
    pthread_cond_init(&t.cond,NULL);
    pthread_t pth_id;
    pthread_create(&pth_id,NULL,thread_func,&t);
    //唤醒子线程
    usleep(1000);
    ret=pthread_cond_signal(&t.cond);
    THREAD_ERR_CHECK(ret,"pthread_cond_signal");
    ret=pthread_join(pth_id,NULL);
    return 0;
}