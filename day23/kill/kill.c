#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int sig=atoi(argv[1]);//注意不要加-
    pid_t pid=atoi(argv[2]);
    int ret=kill(pid,sig);
    ERROR_CHECK(ret,-1,"kill");
    return 0;
}