#include <func.h>

int main()
{
    pid_t pid=fork();
    if(0==pid){
        printf("pid=%d\n",getpid());
        while(1);
    }else{
        printf("pid=%d\n",getpid());
        while(1);
    }
}