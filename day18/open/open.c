#include<func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd;
    //linux非常喜欢使用位权限
    fd=open(argv[1],O_RDWR|O_CREAT);
    ERROR_CHECK(fd,-1,"open");
    char buf[1024]={0};
    int len=read(fd,buf,sizeof(buf));
    printf("buf=%s\n",buf);
    close(fd);
    return 0; 
}