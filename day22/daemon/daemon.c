#include <func.h>

void Daemon()
{
    //创建子进程，父进程退出
    if(fork()!=0)
    {
        exit(0);
    }
    //子进程成立新对话
    setsid();
    //改变工作目录到根
    chdir("/");
    //设置掩码为0
    umask(0);
    //关闭0，1，2等文件描述符
    for(int i=0;i<3;i++){
        close(i);
    }
}

int main()
{
    Daemon();
    while(1);
    return 0;
}