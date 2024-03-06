#include <func.h>

//子线程如何接收参数
void* thread_func(void *p)
{
    printf("I am child thread,%d\n",*(int*)p);
    return NULL;
}
//传递局部变量的地址给子线程
int main()
{
    pthread_t th_id;
    int local=1001;
    int ret=pthread_create(&th_id,NULL,thread_func,&local);//创建线程1
    local=1002;//这里执行更快，把local改掉了，所以子线程1走到打印时，已经被改掉了
    pthread_t th_id1;
    ret=pthread_create(&th_id1,NULL,thread_func,&local);//创建线程2
    printf("I am main thread \n");
    sleep(1);
    return 0;
}