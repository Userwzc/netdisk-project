#include <func.h>

int global=100;
void* thread_func(void *p)
{
    printf("I am child thread,%d\n",global);
    return NULL;
}

int main()
{
    pthread_t th_id;
    int ret=pthread_create(&th_id,NULL,thread_func,NULL);//创建线程
    THREAD_ERR_CHECK(ret,"pthread_create");
    global=200;
    printf("I am main thread \n");
    pthread_join(th_id,NULL);//类似于wait
    return 0;
}