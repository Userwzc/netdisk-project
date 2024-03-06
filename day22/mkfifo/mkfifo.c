#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int ret;
    ret=mkfifo(argv[1],0666);//创建一条有名管道
    ERROR_CHECK(ret,-1,"mkfifo");
    return 0;
}