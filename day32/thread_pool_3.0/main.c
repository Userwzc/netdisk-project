#include "factory.h"

int exit_pipeFd[2];
int exit_flag=0;
void exit_sigfunc(int signum)
{
    printf("要有序退出了\n");
    write(exit_pipeFd[1],"1",1);
    exit_flag=1;
}

int main(int argc,char* argv[])
{
    if(argc!=4)
    {
        printf("./thread_pool IP PORT THREAD_NUM\n");
        return -1;
    }
    //有序退出
    pipe(exit_pipeFd);
    while(fork())
    {
        signal(SIGUSR1,exit_sigfunc);
        wait(NULL);
        if(exit_flag)
        {
            exit(0);
        }
        printf("子进程挂了，或走到异常分支啦，重启它\n");
    }
    //子进程走到下面去

    int threadNum=atoi(argv[3]);//线程数
    printf("threadNum=%d\n",threadNum);
    factory_t f;//主数据结构，线程池工厂
    factoryInit(&f,threadNum); //工厂初始化
    factoryStart(&f);//启动线程
    int sock_fd,new_fd;
    
    tcp_init(argv[1],argv[2],&sock_fd);//网络初始化

    struct sockaddr_in clientAddr;
    socklen_t addrLen;

    taskQueue_t *pQue=&f.taskQueue;
    //注册监控sock_fd
    int epfd=epoll_create(1);
    epoll_add(epfd,sock_fd);

    //注册监控退出管道的读端
    epoll_add(epfd,exit_pipeFd[0]);

    int ready_fd_num,i,j;
    struct epoll_event evs[2];
    while(1)
    {
        ready_fd_num=epoll_wait(epfd,evs,2,-1);
        for(i=0;i<ready_fd_num;i++)
        {
            if(evs[i].data.fd==sock_fd)
            {
                addrLen=sizeof(clientAddr);
                new_fd=accept(sock_fd,(struct sockaddr*)&clientAddr,&addrLen);
                ERROR_CHECK(new_fd,-1,"accept");
                printf("主线程放任务到队列\n");
                //放入队列
                taskEnQueue(pQue,new_fd);
                pthread_cond_signal(&f.cond);//唤醒一个子线程
            }else if(evs[i].data.fd==exit_pipeFd[0])//要退出了
            {
                printf("线程池开始退出\n");
                pthread_mutex_lock(&pQue->mutex);
                f.exitFlag=1;//标记退出
                pthread_mutex_unlock(&pQue->mutex);
                for(j=0;j<threadNum;j++)
                {
                    pthread_cond_signal(&f.cond);//都唤醒
                }
                for(j=0;j<threadNum;j++)
                {
                    pthread_join(f.thidArr[j],NULL);
                }
                printf("线程池退出成功\n");
                exit(0);
            }
        }

     
    }
    close(sock_fd);
    return 0;
}