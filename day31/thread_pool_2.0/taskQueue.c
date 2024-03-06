#include "taskQueue.h"


//任务入队
int taskEnQueue(taskQueue_t *pQueue,int new_fd)
{
    task_t *pnew=(task_t*)calloc(1,sizeof(task_t));//新结点申请空间
    pnew->new_fd=new_fd;
    pthread_mutex_lock(&pQueue->mutex);
    //放队列，尾插法
    if(!pQueue->pRear)
    {
        pQueue->pFront=pnew;
        pQueue->pRear=pnew;
    }else{
        pQueue->pRear->pnext=pnew;
        pQueue->pRear=pnew;
    }
    pQueue->queueSize++;
    pthread_mutex_unlock(&pQueue->mutex);
    return 0;
}

//出队
int taskDequeue(taskQueue_t *pQueue,task_t **pnew)
{
    if(pQueue->queueSize)//需要判断
    {
        *pnew=pQueue->pFront;
        pQueue->pFront=pQueue->pFront->pnext;
        pQueue->queueSize--;//队列长度减1
        if(NULL==pQueue->pFront)//当出队时，队列为空时，队尾要改变
        {
            pQueue->pRear=NULL;
        }
    }else{
        return -1;
    }
    return 0;
}