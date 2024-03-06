#include <func.h>

int main(int argc,char *argv[])
{
    int fdr=open(argv[1],O_RDONLY); //管道读端
    ERROR_CHECK(fdr,-1,"open");
    int fdw=open(argv[2],O_WRONLY);//管道写端
    ERROR_CHECK(fdw,-1,"open");
    printf("fdr=%d,fdw=%d 开始通信\n",fdr,fdw);  
    char buf[1000]={0};
    fd_set readset;
    int ret;
    //struct timeval t; //传入传出参数
    while(1)
    {
        FD_ZERO(&readset); //集合清空
        //让select监控标准输入，fdr
        FD_SET(STDIN_FILENO,&readset);
        FD_SET(fdr,&readset);
        // t.tv_sec=1;
        // t.tv_usec=0;
        int fd_ready_num=select(fdr+1,&readset,NULL,NULL,NULL);
        if(fd_ready_num>0){
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
        else{
            time_t now=time(NULL);
            printf("超时 %s",ctime(&now));
        }
    }
    return 0;
}