#include <func.h>

int sendFd(int pipeFd,int fd)
{
    struct msghdr hdr;
    memset(&hdr,0,sizeof(hdr));

    //用户态必须写一些信息
    struct iovec iov[1];
    char buf[] = "Hello";
    iov[0].iov_base = buf;
    iov[0].iov_len = 5;
    hdr.msg_iov = iov;
    hdr.msg_iovlen = 1;

    size_t cmsglen=CMSG_LEN(sizeof(int));
    struct cmsghdr *pcmsg=(struct cmsghdr *)calloc(1,cmsglen);
    pcmsg->cmsg_len=cmsglen;//第一个成员是结构体本身的长度
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;
    *(int*)CMSG_DATA(pcmsg)=fd;//要传递哪个描述符的控制信息

    //数据部分是文件描述符
    hdr.msg_control = pcmsg;
    hdr.msg_controllen = cmsglen;

    int ret=sendmsg(pipeFd,&hdr,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}

//fd是传出参数
int recvFd(int pipeFd,int *fd)
{
    struct msghdr hdr;
    memset(&hdr,0,sizeof(hdr));

    //用户态必须写一些信息
    struct iovec iov[1];
    char buf[6] = {0};
    iov[0].iov_base = buf;
    iov[0].iov_len = 5;
    hdr.msg_iov = iov;
    hdr.msg_iovlen = 1;

    size_t cmsglen=CMSG_LEN(sizeof(int));
    struct cmsghdr *pcmsg=(struct cmsghdr *)calloc(1,cmsglen);
    pcmsg->cmsg_len=cmsglen;//第一个成员是结构体本身的长度
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;

    //数据部分是文件描述符
    hdr.msg_control = pcmsg;
    hdr.msg_controllen = cmsglen;

    int ret=recvmsg(pipeFd,&hdr,0);
    ERROR_CHECK(ret,-1,"recvmsg");
    *fd=*(int*)CMSG_DATA(pcmsg);//拿到了对应内核控制信息的位置
    return 0;
}



//创建一个子进程，父进程打开普通文件，传递fd给子进程
int main()
{
    int fds[2];
    socketpair(AF_LOCAL,SOCK_STREAM,0,fds);//初始化tcp类型管道
    if(!fork())
    {
        close(fds[1]);//关闭一端
        int fd;
        recvFd(fds[0],&fd);
        printf("I am child %d\n",fd);
        //读文件
        char buf[100]={0};
        read(fd,buf,sizeof(buf));
        printf("buf=%s\n",buf);
    }else{//父进程
        close(fds[0]);//关闭一端
        int fd=open("Readme",O_RDONLY);
        printf("I am parent fd=%d\n",fd);
        sendFd(fds[1],fd);
        wait(NULL);
    }
}