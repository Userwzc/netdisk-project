#include<func.h>

int main(){
    int fd=open("file",O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    printf("\n");//刷新标准输出
    close(STDOUT_FILENO);
    int fd2=dup2(fd,STDOUT_FILENO); //关闭标准输出，并将fd内容复制到stdout中
    printf("fd2=%d\n",fd2); //这句话就写入了file中
    close(fd);
    return 0;  
}