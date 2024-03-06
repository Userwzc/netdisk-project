#include <func.h>

int main(){
    int fd=open("file",O_RDWR|O_CREAT);
    write(fd,"hello",5);
    close(fd);
    return 0;
}