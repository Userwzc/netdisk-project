#include <func.h>

typedef struct{
    int val;
    pthread_mutex_t mutex;
}Share_t,*pShare_t;

#define N 20000000

void* thread_func(void *p)
{
    printf("I am child thread\n");
    pShare_t p1=(pShare_t)p;
    int i;
    for(i=0;i<N;i++)
    {
        pthread_mutex_lock(&p1->mutex);//加锁
        p1->val++;
        pthread_mutex_unlock(&p1->mutex);
    }
    return NULL;
}

int main()
{
    Share_t t={0};
    int ret;
    ret=pthread_mutex_init(&t.mutex,NULL);
    THREAD_ERR_CHECK(ret,"pthread_mutex_init");
    pthread_t pth_id;
    pthread_create(&pth_id,NULL,thread_func,&t);
    int i;
    for(i=0;i<N;i++)
    {
        pthread_mutex_lock(&t.mutex);//主线程加锁
        t.val++;
        pthread_mutex_unlock(&t.mutex);//主线程解锁
    }
    pthread_join(pth_id,NULL);
    printf("main thread result=%d\n",t.val);
    return 0;
}