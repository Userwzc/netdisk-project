#include <func.h>

int main()
{
    int sem_id=semget(1000,1,IPC_CREAT|0600);
    ERROR_CHECK(sem_id,-1,"semget");
    int ret=semctl(sem_id,0,SETVAL,5);
    ERROR_CHECK(ret,-1,"semctl");
    int sem_val;
    sem_val=semctl(sem_id,0,GETVAL);
    ERROR_CHECK(sem_val,-1,"semctl");
    printf("sem_val=%d\n",sem_val);
    return 0;
}