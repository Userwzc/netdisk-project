#include <func.h>

int main(int argc,char *argv[])
{
    int fdw=open(argv[1],O_WRONLY);//管道写端
    ERROR_CHECK(fdw,-1,"open");
    int fdr=open(argv[2],O_RDONLY); //管道读端
    ERROR_CHECK(fdw,-1,"open");
    printf("fdr=%d,fdw=%d 开始通信\n",fdr,fdw);  
    char buf[1000];
    fd_set readset;
    int ret;
    while(1)
    {
        FD_ZERO(&readset); //集合清空
        //让select监控标准输入，fdr
        FD_SET(STDIN_FILENO,&readset);
        FD_SET(fdr,&readset);
        int fd_ready_num=select(fdr+1,&readset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&readset))
        {
            //先读标准输入
            memset(buf,0,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(0==ret){
                printf("我想结束\n");//ctrl d
                break;
            }
            write(fdw,buf,strlen(buf)-1);
        }
        if(FD_ISSET(fdr,&readset))
        {
            memset(buf,0,sizeof(buf));
            ret=read(fdr,buf,sizeof(buf));
            if(0==ret){
                printf("对方断开,再见\n");
                break;
            }
            printf("%s\n",buf);
        }
    }
    return 0;
}