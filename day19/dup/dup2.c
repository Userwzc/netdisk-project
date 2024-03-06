#include<func.h>

int main(){
    int fd=open("file",O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    int fd2=dup2(fd,10); //文件描述符的复制
    printf("fd2=%d\n",fd2);
    close(fd);
    char buf[1024]={0};
    int ret=read(fd2,buf,sizeof(buf));
    ERROR_CHECK(ret,-1,"read");
    puts(buf);
    close(fd2);
    return 0;
}