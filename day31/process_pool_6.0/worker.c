#include "head.h"

int make_child(processData_t* workerList,int childNum)
{
    pid_t pid;
    int i;
    int pipefds[2]; //管道
    for(i=0;i<childNum;i++)
    {
        socketpair(AF_LOCAL,SOCK_STREAM,0,pipefds);//初始化tcp类型的管道
        pid=fork();
        if(0==pid)
        {
            close(pipefds[1]);
            handleEvent(pipefds[0]);
        }
        close(pipefds[0]);
        workerList[i].pid=pid;
        workerList[i].status=FREE;
        workerList[i].pipeFd=pipefds[1];
#ifdef DEBUG
        printf("workerList[%d].pipeFd=%d\n",i,workerList[i].pipeFd);
#endif
    }
    return 0;
}

int handleEvent(int pipeFd)
{
    int new_fd,finish_flag=1;
    int exit_flag=0;
    while(1)
    {
        //收到任务
        recvFd(pipeFd,&new_fd,&exit_flag);
        if(exit_flag)
        {
            printf("child exit\n");
            exit(0);
        }
        printf("recv parent task %d\n",new_fd);
        //给客户端发文件
        transFile(new_fd);
        printf("发送文件成功\n");
        close(new_fd);
        //通知父进程完成任务
        write(pipeFd,&finish_flag,sizeof(int));
    }
}
