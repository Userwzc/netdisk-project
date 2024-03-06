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
    int ret;
    ret=recvn(new_fd,&recvLen,4);
    if(-1==ret)
    {
        return -1;
    }
    recvn(new_fd,buf,recvLen);
    printf("buf=%s\n",buf);
    int fd=open(buf,O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");

    //接文件大小
    off_t fileSize;//总长度
    recvn(new_fd,&recvLen,4);
    recvn(new_fd,&fileSize,recvLen);

    struct timeval start,end;
    gettimeofday(&start,NULL);
    //首先通过ftruncate去做一个对应大小的文件
    // int ret;
    // ret=ftruncate(fd,fileSize);
    // ERROR_CHECK(ret,-1,"ftruncate");

    off_t downLoadSize=0;
    off_t lastSize=0;
    off_t slice=fileSize/100;//每百分之一


    //接文件内容,接1000的整数倍
    // while(fileSize-downLoadSize>=1000)
    // {
    //     recvn(new_fd,p+downLoadSize,1000);//接recvLen长度的数据
    //     downLoadSize+=1000;
    //     if(downLoadSize-lastSize>slice)
    //     {
    //         printf("%5.2lf%%\r", 100.0*downLoadSize/fileSize);
    //         fflush(stdout);
    //         lastSize = downLoadSize;
    //     }
    // }
    // recvn(new_fd,p+downLoadSize,fileSize-downLoadSize); //接最后小于1000个字节的部分
    int pipefds[2];
    pipe(pipefds);//初始化管道
    int total = 0;
    while(total < fileSize){
        //从new_fd读取4096字节数据，写入管道,ret是代表写入管道的数据量
        int ret =splice(new_fd,NULL,pipefds[1],NULL,4096,SPLICE_F_MORE);
        if(ret<=0)
        {
            printf("对端断开了\n");
            break;
        }
        total += ret;
        if(total-lastSize>slice)
        {
            printf("%5.2lf%%\r", 100.0*total/fileSize);
            fflush(stdout);
            lastSize = total;
        }
        //从管道中读取数据，写入到文件，写ret个字节
        ret=splice(pipefds[0],NULL,fd,NULL,ret,SPLICE_F_MORE);
        if(ret<=0)
        {
            printf("对端断开了\n");
            break;
        }
    }
    printf("100.00%%\n");
    gettimeofday(&end,NULL);
    //统计下载总时间
    printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    close(fd);//关闭文件
    return 0;
}