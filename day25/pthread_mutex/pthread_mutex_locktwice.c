#include <func.h>

typedef struct{
    int val;
    pthread_mutex_t mutex;
}Share_t,*pShare_t;


void* thread_func(void *p)
{
    pthread_mutex_lock(&((pShare_t)p)->mutex);//加锁
    printf("I am child thread\n");
    pthread_mutex_unlock(&((pShare_t)p)->mutex);//解锁
    return NULL;
}
//递归锁是一个线程可以对某把锁加锁多次，解锁也需要解锁多次
int main()
{
    Share_t t;
    int ret;
    pthread_mutexattr_t mutex_attr;
    //锁属性进行初始化
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_settype(&mutex_attr,PTHREAD_MUTEX_RECURSIVE);
    ret=pthread_mutex_init(&t.mutex,&mutex_attr);//初始化一把递归锁
    THREAD_ERR_CHECK(ret,"pthread_mutex_init");
    pthread_t pth_id;
    pthread_create(&pth_id,NULL,thread_func,&t);
    printf("main start unlock\n");
    pthread_mutex_lock(&t.mutex);//主线程加锁
    printf("lock first success\n");
    pthread_mutex_lock(&t.mutex);
    printf("lock second success\n");
    pthread_mutex_unlock(&t.mutex);
    pthread_mutex_unlock(&t.mutex);
    pthread_join(pth_id,NULL);
    printf("main thread\n");
    return 0;
}