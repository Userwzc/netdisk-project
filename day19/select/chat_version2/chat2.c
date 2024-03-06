#include <func.h>

int main(int argc,char *argv[])
{
    int fdw=open(argv[1],O_WRONLY);//管道写端
    ERROR_CHECK(fdw,-1,"open");
    int fdr=open(argv[2],O_RDONLY); //管道读端
    ERROR_CHECK(fdw,-1,"open");
    printf("fdr=%d,fdw=%d 开始通信\n",fdr,fdw);  
    char buf[1000]={0};
    while(1)
    {
        memset(buf,0,sizeof(buf));
        read(fdr,buf,sizeof(buf));
        printf("%s",buf);
        memset(buf,0,sizeof(buf));
        read(STDIN_FILENO,buf,sizeof(buf));
        write(fdw,buf,strlen(buf));
    }
    return 0;
}