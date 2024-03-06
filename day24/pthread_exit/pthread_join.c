#include <func.h>


void* thread_func(void *p)
{
    printf("I am child thread,%lu\n",pthread_self());
    char *tret = (char *)malloc(20);
    strcpy(tret,"hello");
    return tret;
}

int main()
{
    pthread_t th_id;
    int ret=pthread_create(&th_id,NULL,thread_func,NULL);//创建线程
    // THREAD_ERR_CHECK(ret,"pthread_create");
    char *pret=NULL;//用来接子线程的返回值
    ret=pthread_join(th_id,(void**)&pret);//类似于wait
    THREAD_ERR_CHECK(ret,"pthread_join");
    printf("I am main thread %s\n",pret);
    return 0;
}