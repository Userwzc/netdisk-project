#include <func.h>
#define N 10000000
int main(){
    int shmid;
    shmid=shmget(1000,4096,0600|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    int *p=(int*)shmat(shmid,NULL,0);
    p[0]=0;
    if(!fork()){
        int i;
        for(i=0;i<N;i++){
            p[0]++; //不是原子操作
        }
        exit(0);
    }else{
        int i;
        for(i=0;i<N;i++){
            p[0]++;
        }
        wait(NULL);
        printf("p[0]=%d\n",p[0]);
        return 0;
    }
}
