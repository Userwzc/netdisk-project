#include <func.h>
int main()
{
    int fds[2];
    pipe(fds); //fds[0]管道的读端，fds[1]就是管道写端
    if(!fork()){
        //如果子进程写数据，关闭读端
        close(fds[0]);
        write(fds[1],"hello",5);
        exit(0);
    }else{
        //父进程往管道读数据,关闭写端
        close(fds[1]);
        char buf[1000]={0};
        read(fds[0],buf,sizeof(buf));//子进程读管道
        puts(buf);
        wait(NULL);
        exit(0);
    }
}