#include "factory.h"

int factoryInit(factory_t *pFactory,int threadNum)
{
    int ret;
    bzero(pFactory,sizeof(factory_t));
    pFactory->thidArr=(pthread_t*)calloc(threadNum,sizeof(pthread_t)); //线程id空间
    pFactory->threadNum=threadNum;//线程数目初始化
    ret=pthread_cond_init(&pFactory->cond,NULL);//条件变量初始化
    THREAD_ERR_CHECK(ret,"pthread_cond_init");
    pthread_mutex_init(&pFactory->taskQueue.mutex,NULL);//锁初始化
    // pFactory->exitFlag=0;
    return 0;
}

//启动子线程
int factoryStart(factory_t *pFactory)
{
    int i,ret;
    for(i=0;i<pFactory->threadNum;i++)
    {
        ret=pthread_create(pFactory->thidArr+i,NULL,threadFunc,pFactory);
        THREAD_ERR_CHECK(ret,"pthread_create");
    }
}


//注册监控某个描述符是否可读
int epoll_add(int epfd,int fd)
{
    struct epoll_event event;
    event.data.fd=fd;
    event.events=EPOLLIN;
    int ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    return 0;
}