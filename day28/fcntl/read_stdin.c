#include <func.h>

int setNonblock(int fd)
{
    int status;
    status=fcntl(fd,F_GETFL);//获取描述符状态
    status=status|O_NONBLOCK;//增加非阻塞
    int ret;
    ret=fcntl(fd,F_SETFL,status);
    ERROR_CHECK(ret,-1,"fcntl");
}


int main()
{
    char buf[100]={0};
    int ret;
    sleep(6);
    setNonblock(STDIN_FILENO);//修改标准输入为非阻塞
    ret=read(STDIN_FILENO,buf,sizeof(buf));//非阻塞情况下，缓冲区没有数据，返回-1
    printf("ret=%d,buf=%s\n",ret,buf);
    return 0;
}