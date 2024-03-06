#include <func.h>

int main()
{
    int fds[2];
    pipe(fds);
    if(!fork())
    {
        //如果子进程写数据，关闭读端
        close(fds[0]);
        while(1)
        {
            write(fds[1],"h",1);
        }
    }else{
        //父进程往管道读数据，关闭写端
        close(fds[1]);
        char buf[1000]={0};
        while(1)
        {
            read(fds[0],buf,1);//父进程读管道
            puts(buf);
        }
        wait(NULL);
        exit(0);
    }
}