//编写程序，打印当前进程pid，父进程pid，真实用户ID，真实组ID，有效用户ID，有效组ID
#include <func.h>

int main()
{
    printf("pid=%d,ppid=%d,uid=%d,gid=%d,euid=%d,egid=%d\n",getpid(),getppid(),
    getuid(),getgid(),geteuid(),getegid());
    return 0;
}