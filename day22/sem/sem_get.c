#include <func.h>

int main()
{
    int sem_id=semget(1000,1,IPC_CREAT|0600);
    ERROR_CHECK(sem_id,-1,"semget");
    return 0;
}