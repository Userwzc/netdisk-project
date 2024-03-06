#include <func.h>

int main()
{
    int fd=open("file",O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    pid_t pid=fork();
    if(0==pid)
    {
        char buf[1000]={0};
        read(fd,buf,5);
        printf("I am child fd=%d read %s\n",fd,buf);
    }else{
        //父进程fork的返回值是子进程的pid
        char buf1[1000]={0};
        read(fd,buf1,5);
        close(fd);
        printf("I am parent fd=%d read %s\n",fd,buf1);
    }
    return 0;
}