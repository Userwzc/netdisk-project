#include <func.h>
//子进程结束，父进程通过wait拿子进程的退出码
int main()
{
    pid_t pid=fork();
    if(pid==0)
    {
        printf("I am child %d,ppid=%d\n",getpid(),getppid());
        sleep(5);
        return 123;
    }else{
        printf("i am parent %d\n",getpid());
        int child_status; //拿子进程状态
        //child_status 存储两个内容，1知道子进程是否崩溃 2退出码
        int ret=waitpid(pid,&child_status,WNOHANG);//和wait等价
        if(ret>0)
        {
            if(WIFEXITED(child_status))
            {
                printf("exit successfully,exit code =%d\n",WEXITSTATUS(child_status));
            }else if(WIFSIGNALED(child_status)){
                printf("erupted,exit code =%d\n",WTERMSIG(child_status));
            }
            printf("回收 %d 成功\n",ret);
        }
        else{
            printf("没有回收成功%d\n",ret);
        }
    }
    return 0;
}