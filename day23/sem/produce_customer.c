#include <func.h>

int main()
{
    int shmid=shmget(1000,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    int *p=(int*)shmat(shmid,NULL,0);
    int semArrid=semget(1000,1,IPC_CREAT|0600);
    ERROR_CHECK(semArrid,-1,"semget");
    int ret=semctl(semArrid,0,SETVAL,1);
    ERROR_CHECK(ret,-1,"semctl SETVAL");
    struct sembuf P;
    P.sem_num=0;
    P.sem_op=-1;
    P.sem_flg=SEM_UNDO;
    struct sembuf V;
    V.sem_num=0;
    V.sem_op=1;
    V.sem_flg=SEM_UNDO;
    p[0]=0;
    p[1]=10;
    if(!fork())
    {
        //子进程是消费者
        while(1)
        {
            sleep(2);
            printf("i am consumer,before consume,product=%d,space=%d\n",p[0],p[1]);
            semop(semArrid,&P,1);
            if(p[0]>0)
            {
                --p[0];
                printf("buy a product\n");
                p[1]++;
            }
            semop(semArrid,&V,1);
            printf("i am consumer,after consume,product=%d,spcae=%d\n",p[0],p[1]);
        }
    }else{
        while(1)
        {
            //父进程是生产者
            sleep(1);
            printf("i am producer,before produce,product=%d,spcae=%d\n",p[0],p[1]);
            semop(semArrid,&P,1);
            if(p[1]>0)
            {
                --p[1];
                printf("Produce a product\n");
                ++p[0];
            }
            semop(semArrid,&V,1);
            printf("i am producer,after produce,product=%d,space=%d\n",p[0],p[1]);
        }
    }
}