#include <func.h>

int main()
{
    int shmid;
    //第一次是创建，如果是另外一个进程，就是通过shmget获取shmid
    shmid=shmget(1000,4096,0600|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    //连接到本进程的进程地址空间内
    char *p=(char*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char*)-1,"shmat");
    strcpy(p,"I love you");//往共享内存放数据
    shmdt(p);//解除连接
    return 0;
}