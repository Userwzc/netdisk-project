#include<func.h>

int main(){
    int fd=open("file",O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    int fd2=fd;
    close(fd);
    char buf[1024]={0};
    int ret=read(fd2,buf,sizeof(buf));
    ERROR_CHECK(ret,-1,"read");
    puts(buf);
    return 0;
}