#include <func.h>

int print()
{
    printf("I am print\n");
    pthread_exit(NULL);
    return 0;
}

void* thread_func(void *p)
{
    print();
    printf("I am child thread,%lu\n",pthread_self());
    return NULL;
}

int main()
{
    pthread_t th_id;
    int ret=pthread_create(&th_id,NULL,thread_func,NULL);//创建线程
    // THREAD_ERR_CHECK(ret,"pthread_create");
    pthread_join(th_id,NULL);//类似于wait
    printf("I am main thread %lu\n",pthread_self());
    return 0;
}