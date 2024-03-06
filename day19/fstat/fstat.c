#include <func.h>

int main(){
    int fd;
    fd=open("file",O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    int ret;
    struct stat buf;
    ret=fstat(fd,&buf);
    ERROR_CHECK(ret,-1,"fstat");
    printf("size =%ld\n",buf.st_size);
    close(fd);
    return 0;
}