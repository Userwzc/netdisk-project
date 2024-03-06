#include <func.h>

#define N 10000000
int main()
{
    int shmid;
    //第一次是创建，如果是另外一个进程，就是通过shmget获取shmid
    shmid=shmget(1000,4096,0600|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    //连接到本进程的进程地址空间内
    int *p=(int*)shmat(shmid,NULL,0);
    p[0]=20000000;
    if(!fork())
    {
        int i;
        for(i=0;i<N;i++)
        {
            p[0]--;//不是原子操作
        }
        exit(0);
    }else{
        int i;
        for(i=0;i<N;i++)
        {
            p[0]--;
        }
        wait(NULL);
        printf("p[0]=%d\n",p[0]);
        return 0;
    }
}