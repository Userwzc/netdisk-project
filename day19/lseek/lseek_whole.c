#include <func.h>

int main(){
    int fd;
    fd=open("file",O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    char buf[1024]={0};
    off_t offset=lseek(fd,1000,SEEK_SET); //相对于开头偏移1000
    ERROR_CHECK(offset,-1,"lseek");
    int ret=write(fd,"a",1);
    ERROR_CHECK(ret,-1,"write");
    return 0;
}