#include <func.h>

int main(){
    pid_t pid=fork();
    if(0==pid){
        printf("i am child\n");
        while(1);
    }else{
        printf("i am parent\n");
    }
    return 0;
}