#include <func.h>

int main()
{
    int shmid;
    //第一次是创建,如果是另外一个进程，就是通过shmget获取shmid
    shmid=shmget(1000,4096,0600|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    return 0;
}