#include <func.h>

int main()
{
    int shmid;
    //第一次是创建，如果是另外一个进程，就是通过shmget获取shmid
    shmid=shmget(1000,4096,0600|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    int ret;
    struct shmid_ds stat; //创建结构体
    ret=shmctl(shmid,IPC_STAT,&stat);//获取共享内存段属性信息
    ERROR_CHECK(ret,-1,"shmctl");
    printf("cuid = %d perm = %o size= %ld nattch =%ld\n",
    stat.shm_perm.cuid,stat.shm_perm.mode,stat.shm_segsz,stat.shm_nattch);
    return 0;
}