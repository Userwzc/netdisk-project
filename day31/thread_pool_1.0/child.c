//子线程函数放这里
#include "factory.h"

void cleanup(void *p)
{
    pthread_mutex_t *pmutex=(pthread_mutex_t *)p;
    pthread_mutex_unlock(pmutex);//解锁
}

//子线程流程
void * threadFunc(void* p)
{
    factory_t *pFactory=(factory_t *)p;
    taskQueue_t *pQue=&pFactory->taskQueue;
    task_t *pnew;
    int taskFlag;//是否拿到任务
    while(1)
    {
        pthread_mutex_lock(&pQue->mutex);//加锁
        pthread_cleanup_push(cleanup,&pQue->mutex);//清理函数
        if(!pQue->queueSize)//判断队列为空
        {
            pthread_cond_wait(&pFactory->cond,&pQue->mutex);//睡觉
        }
        //出队
        taskFlag=taskDequeue(pQue,&pnew);
        pthread_cleanup_pop(1);//通过pop去解锁
        if(!taskFlag)//拿到任务后
        {
            printf("send file\n");
            transFile(pnew->new_fd);
            close(pnew->new_fd);
            free(pnew);
        }
    }
}