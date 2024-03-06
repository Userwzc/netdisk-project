#include "head.h"

//发送文件
int transFile(int new_fd)
{
    //先发文件名
    train_t t;
    t.size=strlen("file");
    strcpy(t.buf,"file");
    send(new_fd,&t,4+t.size,0);
    //再发文件内容
    int fd=open("file",O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    int ret;
    //边读边发
    while(t.size=read(fd,t.buf,sizeof(t.buf)))
    {
        ret=send(new_fd,&t,4+t.size,0);
        if(-1==ret)
        {
            goto end;//客户端在接收过程中，断开了，就退出
        }
    }
    //文件内容发送结束
    t.size=0;
    send(new_fd,&t,4+t.size,0);
end:
    close(fd);
    return 0;
}

//循环接收，要接多少字节，接完才会返回
int recvn(int new_fd,void* pStart,int len)
{
    int total=0,ret;
    char *p=(char*)pStart;
    while(total<len)
    {
        ret=recv(new_fd,p+total,len-total,0);
        ERROR_CHECK(ret,-1,"recv");
        if(0==ret)
        {
            return -1; //对端断开了，返回-1
        }
        total+=ret;
    }
    return 0;
}

//接收文件
int recvFile(int new_fd)
{
    int recvlen;
    char buf[1000]={0};
    recvn(new_fd,&recvlen,4);
    recvn(new_fd,buf,recvlen);
    printf("buf=%s\n",buf);
    int fd=open(buf,O_WRONLY|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");

    //再接文件内容
    while(1)
    {
        recvn(new_fd,&recvlen,4);
        if(recvlen>0)
        {
            recvn(new_fd,buf,recvlen);
            write(fd,buf,recvlen);
        }
        else{
            break;
        }
    }
    close(fd);// 关闭文件
    return 0;
}