#include <func.h>

//tcp client
int main(int argc,char* argv[])
{
    int client_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(client_fd,-1,"socket");
    //定义结构体，存ip和端口
    struct sockaddr_in serAddr;
    memset(&serAddr,0,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);
    serAddr.sin_port=htons(atoi(argv[2]));
    int ret=connect(client_fd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"connect");
    //读集合
    fd_set rdset;
    char buf[1000];
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(client_fd,&rdset);
        select(client_fd+1,&rdset,NULL,NULL,NULL);
        //如果标准输入可读
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
            memset(buf,0,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));//读取标准输入
            send(client_fd,buf,strlen(buf)-1,0);//数据发送给对方
        }
        if(FD_ISSET(client_fd,&rdset))
        {
            memset(buf,0,sizeof(buf));
            ret=recv(client_fd,buf,sizeof(buf),0);//接收数据
            if(ret==0)
            {
                printf("对方断开了\n");
                break;
            }
            printf("%s\n",buf);
        }
    }
    close(client_fd);
}