#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd;
    fd=open(argv[1],O_RDWR|O_CREAT|O_APPEND,0666);   //文件不存在就会创建
    ERROR_CHECK(fd,-1,"open");
    printf("fd=%d\n",fd);
    char buf[1024]={0};
    int ret=read(fd,buf,10);     //append不影响读
    puts(buf);
    return 0;
}