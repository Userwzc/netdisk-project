#include <func.h>

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

    //接文件大小
    off_t fileSize;
    recvn(new_fd,&recvLen,4);
    recvn(new_fd,&fileSize,recvLen);

    struct timeval start,end;
    gettimeofday(&start,NULL);
    //首先通过ftruncate去做一个对应大小的文件
    int ret=ftruncate(fd,fileSize);
    ERROR_CHECK(ret,-1,"ftruncate");

    //mmap映射
    char *p=(char*)mmap(NULL,fileSize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,(char*)-1,"mmap");

    off_t downLoadSize=0;
    off_t lastSize=0;
    off_t slice=fileSize/100;//每百分之一

    recvn(new_fd,p,fileSize);
    ret=munmap(p,fileSize);
    ERROR_CHECK(ret,-1,"munmap");
    printf("100.00%%\n");
    gettimeofday(&end,NULL);
    printf("use time =%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    close(fd);//关闭文件
    return 0;
}