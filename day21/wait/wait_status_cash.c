#include <func.h>
//子进程结束，父进程通过wait拿子进程的退出码
int main()
{
    pid_t pid=fork();
    if(pid==0)
    {
        printf("I am child %d,ppid=%d\n",getpid(),getppid());
        char *p=NULL;
        *p='a';
        return 0;
    }else{
        printf("i am parent %d\n",getpid());
        pid_t child_pid;
        int child_status; //拿子进程状态
        //child_status 存储两个内容，1知道子进程是否崩溃 2退出码
        child_pid=wait(&child_status);
        if(WIFEXITED(child_status))
        {
            printf("exit successfully,exit code =%d\n",WEXITSTATUS(child_status));
        }else{
            printf("erupted,exit code =%d\n",WTERMSIG(child_status));
        }
        printf("回收 %d 成功\n",child_pid);
    }
}