#include <func.h>

void *thread_func(void *p)
{
    printf("I am child thread,%lu\n",pthread_self());
    return (void*)1;
}

int main()
{
    pthread_t th_id;
    int ret=pthread_create(&th_id,NULL,thread_func,NULL);
    THREAD_ERR_CHECK(ret,"pthread_create");
    long thread_ret;
    ret=pthread_join(th_id,(void**)&thread_ret);
    THREAD_ERR_CHECK(ret,"pthread_join");
    printf("I am main thread %ld\n",thread_ret);
    return 0;
}