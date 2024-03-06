#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__
#include "head.h"

typedef struct task_n{
    int new_fd;
    struct task_n* pnext;
}task_t;


typedef struct{
    task_t *pFront;//队列头
    task_t *pRear;//队列尾
    pthread_mutex_t mutex;//锁
    int queueSize;//当前任务的个数

}taskQueue_t;

//入队
int taskEnQueue(taskQueue_t *pQueue,int new_fd);
//出队
int taskDequeue(taskQueue_t *pQueue,task_t **pnew);
#endif