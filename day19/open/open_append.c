#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd;
    fd=open(argv[1],O_RDWR|O_CREAT|O_APPEND,0666);   //文件不存在就会创建
    ERROR_CHECK(fd,-1,"open");
    printf("fd=%d\n",fd);
    int ret=write(fd,"world",5);    //append在每次调用write的时候指向文件末尾
    return 0;
}