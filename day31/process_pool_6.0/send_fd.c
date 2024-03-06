#include "head.h"

int sendFd(int pipeFd,int fd,int exit_flag)
{
    struct msghdr hdr;
    memset(&hdr,0,sizeof(hdr));

    //用户态必须写一些信息
    struct iovec iov[1];
    iov[0].iov_base=&exit_flag;
    iov[0].iov_len=4;
    hdr.msg_iov=iov;
    hdr.msg_iovlen=1;
    
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
int recvFd(int pipeFd,int *fd,int *exit_flag)
{
    struct msghdr hdr;
    memset(&hdr,0,sizeof(hdr));

    //用户态必须写一些信息
    struct iovec iov[1];
    iov[0].iov_base = exit_flag;
    iov[0].iov_len = 4;
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