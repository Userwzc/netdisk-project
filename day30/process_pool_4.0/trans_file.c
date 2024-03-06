#include "head.h"

//发送文件
int transFile(int new_fd)
{
    //先发文件名，现在固定文件名叫 file
    train_t t;
    t.size=strlen("file");//火车头存长度
    strcpy(t.buf,"file");//火车内容是文件名
    send(new_fd,&t,4+t.size,0);
    //再发文件内容
    int fd=open("file",O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    
    //发送文件大小给客户端
    struct stat file_buf;
    fstat(fd,&file_buf);
    t.size=sizeof(file_buf.st_size);
    memcpy(t.buf,&file_buf.st_size,sizeof(file_buf.st_size));
    send(new_fd,&t,4+t.size,0);

    char *p=(char*)mmap(NULL,file_buf.st_size,PROT_READ,MAP_SHARED,fd,0);
    ERROR_CHECK(p,(char*)-1,"mmap");

    long ret=send(new_fd,p,file_buf.st_size,0);
    printf("send bytes=%ld\n",ret);
    munmap(p,file_buf.st_size);
end:
    close(fd);
    return 0;
}

//循环接收，要接多少字节，接完那么多才会返回
int recvn(int new_fd,void* pStart,int len)
{
    int total=0,ret;
    char *p=(char*)pStart;
    while(total<len)
    {
        ret=recv(new_fd,p+total,len-total,0);//ret是接收到的字节数
        ERROR_CHECK(ret,-1,"recv");
        if(0==ret)
        {
            return -1;//对端断开了，返回-1
        }
        total+=ret;
    }
    return 0;
}

//接收文件
int recvFile(int new_fd)
{
    //先接文件名,每次先接4个字节
    int recvLen;
    char buf[1000]={0};
    recvn(new_fd,&recvLen,4);
    recvn(new_fd,buf,recvLen);
    printf("buf=%s\n",buf);
    int fd=open(buf,O_WRONLY|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");

    //再接文件内容
    while(1)
    {
        recvn(new_fd,&recvLen,4);//接火车车厢
        if(recvLen>0)
        {
            recvn(new_fd,buf,recvLen);//接recvLen长度的数据
            write(fd,buf,recvLen);//把接收到的内容写入文件
        }else{
            break;
        }
    }
    close(fd);//关闭文件
    return 0;
}