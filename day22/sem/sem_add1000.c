#include <func.h>
#define N 10000000
int main()
{
    int shmid;
    shmid=shmget(1000,4096,0600|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    int *p=(int*)shmat(shmid,NULL,0);
    p[0]=0;
    int sem_id=semget(1000,1,0600|IPC_CREAT);     //获取key为1000的信号量集合
    ERROR_CHECK(sem_id,-1,"semget");
    int ret=semctl(sem_id,0,SETVAL,1);     //初始化信号量为1
    ERROR_CHECK(ret,-1,"semctl");
    struct sembuf P;
    P.sem_num=0;  //信号量在集合中的下标
    P.sem_op=-1;  //信号量修改
    P.sem_flg=SEM_UNDO;  //如果p操作被终止，会自动恢复
    struct sembuf V;
    V.sem_num=0;
    V.sem_op=1;
    V.sem_flg=SEM_UNDO;
    if(!fork())
    {
        for(int i=0;i<N;i++)
        {
            semop(sem_id,&P,1);
            p[0]++;
            semop(sem_id,&V,1);
        }
        exit(0);
    }else{
        for(int i=0;i<N;i++)
        {
            semop(sem_id,&P,1);
            p[0]++;
            semop(sem_id,&V,1);
        }
        wait(NULL);
        printf("p[0]=%d\n",p[0]);
        return 0;
    }
}