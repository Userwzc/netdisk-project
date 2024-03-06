#include <func.h>
//子进程结束，父进程通过wait回收子进程的pcb
int main()
{
    pid_t pid=fork();
    if(pid==0)
    {
        printf("I am child %d,ppid=%d\n",getpid(),getppid());
        sleep(5);
        return 0;
    }else{
        printf("i am parent %d\n",getpid());
        pid_t child_pid;
        child_pid=wait(NULL);
        printf("回收 %d 成功\n",child_pid);
    }
}