#include <func.h>

int main(){
    int fd;
    fd=open("file",O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    char buf[1024]={0};
    off_t offset=lseek(fd,5,SEEK_SET);
    ERROR_CHECK(offset,-1,"lseek");
    printf("offset=%ld\n",offset);
    int ret=write(fd,"howareyou",9);
    ERROR_CHECK(ret,-1,"write");
    return 0;
}