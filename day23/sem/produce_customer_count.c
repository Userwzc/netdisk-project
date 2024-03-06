#include <func.h>
int main()
{
    int semArrid=semget(1000,2,IPC_CREAT|0600);
    ERROR_CHECK(semArrid,-1,"semget");
    unsigned short arr[2]={0,10};
    semctl(semArrid,0,SETALL,arr);
    if(!fork())
    {
        //子进程是消费者
        struct sembuf c[2];
        c[0].sem_num=0;
        c[0].sem_op=-1;
        c[0].sem_flg=SEM_UNDO;
        c[1].sem_num=1;
        c[1].sem_op=1;
        c[1].sem_flg=SEM_UNDO;
        while(1)
        {
            sleep(2);
            printf("i am consumer,before consume,product =%d,space=%d\n"
            ,semctl(semArrid,0,GETVAL),semctl(semArrid,1,GETVAL));
            semop(semArrid,&c[0],1);
            printf("buy a product\n");
            semop(semArrid,&c[1],1);
            printf("i am consumer,after consume,product =%d,space=%d\n"
            ,semctl(semArrid,0,GETVAL),semctl(semArrid,1,GETVAL));
        }
        exit(0);
    }else{
        struct sembuf p[2];
        p[0].sem_num=0;
        p[0].sem_op=1;
        p[0].sem_flg=SEM_UNDO;
        p[1].sem_num=1;
        p[1].sem_op=-1;
        p[1].sem_flg=SEM_UNDO;
        while(1)
        {
            sleep(1);
            printf("i am producer,before produce,product =%d,space=%d\n"
            ,semctl(semArrid,0,GETVAL),semctl(semArrid,1,GETVAL));
            semop(semArrid,&p[1],1);
            printf("produce a product\n");
            semop(semArrid,&p[0],1);
            printf("i am producer,after produce,product =%d,space=%d\n"
            ,semctl(semArrid,0,GETVAL),semctl(semArrid,1,GETVAL));
        }
        wait(NULL);
    }
    return 0;
}