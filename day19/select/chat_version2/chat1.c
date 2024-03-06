#include <func.h>

int main(int argc,char *argv[])
{
    int fdr=open(argv[1],O_RDONLY); //管道读端
    ERROR_CHECK(fdr,-1,"open");
    int fdw=open(argv[2],O_WRONLY);//管道写端
    ERROR_CHECK(fdw,-1,"open");
    printf("fdr=%d,fdw=%d 开始通信\n",fdr,fdw);  
    char buf[1000]={0};
    while(1){
        //先读标准输入
        memset(buf,0,sizeof(buf));
        read(STDIN_FILENO,buf,sizeof(buf));
        //发送给对方
        write(fdw,buf,strlen(buf));
        memset(buf,0,sizeof(buf));
        int ret=read(fdr,buf,sizeof(buf)); //读管道时，管道内没有数据会阻塞
        ERROR_CHECK(ret,-1,"read");
        printf("%s",buf);
    }
    return 0;
}