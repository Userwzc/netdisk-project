#include <func.h>

void* thread_func(void *p)
{
    printf("I am child thread,%lu\n",pthread_self());
    return NULL;
}
int main()
{
    pthread_t th_id;
    struct timeval start,end;
    gettimeofday(&start,NULL);
    int ret =pthread_create(&th_id,NULL,thread_func,NULL);//创建线程
    pthread_join(th_id,NULL); //类似于wait
    gettimeofday(&end,NULL);
    printf("usetime=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    printf("I am main thread %lu\n",pthread_self());
    return 0;
}