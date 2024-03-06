#include <func.h>

int main(){
    int fd;
    fd=open("file",O_WRONLY);
    ERROR_CHECK(fd,-1,"open");
    int ret = ftruncate(fd,5);
    ERROR_CHECK(ret,-1,"ftruncate");
    close(fd);
    return 0;
}