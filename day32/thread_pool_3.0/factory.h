#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "taskQueue.h"

typedef struct{
    pthread_t *thidArr;//存线程id的起始地址
    int threadNum;//线程数目
    pthread_cond_t cond;//条件变量
    taskQueue_t taskQueue;//队列
    int exitFlag;//0代表运行，1代表要退出
}factory_t;

//工厂初始化
int factoryInit(factory_t *pFactory, int threadNum);
//工厂启动
int factoryStart(factory_t *pFactory);

//子线程函数
void * threadFunc(void* p);

//socket,bind,listen的初始化
int tcp_init(char* ip,char* port,int *sfd);

//发送文件
int transFile(int new_fd);

//注册监控某个描述符是否可读
int epoll_add(int epfd,int fd);
#endif