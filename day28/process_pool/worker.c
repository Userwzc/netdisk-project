#include "head.h"

int make_child(processData_t* workerList,int childNum)
{
    int i;
    pid_t pid;
    for(i=0;i<childNum;i++)
    {
        pid=fork();
        if(0==pid)
        {
            handleEvent();
        }
        //父进程才会走到这里,保存子进程pid，初始化子进程状态
        workerList[i].pid=pid;
        workerList[i].status=FREE;
    }
    return 0;
}

int handleEvent()
{
    while(1);
}