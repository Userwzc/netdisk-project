#include <func.h>

int main()
{
    int semArrid=semget(1000,2,IPC_CREAT|0600);
    ERROR_CHECK(semArrid,-1,"semget");
    unsigned short arr[2]={3,5};
    int ret=semctl(semArrid,0,SETALL,arr); //第二个参数无效
    ERROR_CHECK(ret,-1,"semctl SETALL");
    unsigned short retArr[2]={0};
    ret=semctl(semArrid,0,GETALL,retArr);
    ERROR_CHECK(ret,-1,"semctl GETALL");
    for(int i=0;i<2;i++){
        printf("retArr[%d]=%d\n",i,retArr[i]);
    }
    return 0;
}