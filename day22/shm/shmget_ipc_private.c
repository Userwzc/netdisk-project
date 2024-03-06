#include <func.h>

int main()
{
    int shmid;
    //私有方式创建共享内存，只能在亲缘关系进程之间使用
    shmid=shmget(IPC_PRIVATE,4096,0600|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    if(!fork())
    {
        //连接到本进程的进程地址空间内
        char *p=(char*)shmat(shmid,NULL,0);
        ERROR_CHECK(p,(char*)-1,"shmat");
        strcpy(p,"hello");
    }else{
        //连接到本进程的进程地址空间内
        char *p=(char*)shmat(shmid,NULL,0);
        ERROR_CHECK(p,(char*)-1,"shmat");
        wait(NULL);
        puts(p);
    }
    return 0;
}