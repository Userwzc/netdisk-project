#include<func.h>

int main(){
    int fd=open("file",O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    printf("\n");//刷新标准输出
    close(STDOUT_FILENO);
    int fd2=dup(fd); //文件描述符的复制,是系统调用
    printf("fd2=%d\n",fd2); //这句话就写入了file中
    close(fd);
    return 0;  
}