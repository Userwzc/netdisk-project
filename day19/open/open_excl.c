#include <func.h>
//与O_CREAT连用
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd;
    fd=open(argv[1],O_RDWR|O_CREAT|O_EXCL,0666);   //文件不存在就会创建,文件存储就会open失败
    ERROR_CHECK(fd,-1,"open");
    printf("fd=%d\n",fd);
    return 0;
}