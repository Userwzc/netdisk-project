#include <func.h>

//tcp server
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int sock_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sock_fd,-1,"sock_fd");
    //定义结构体，存ip和端口
    struct sockaddr_in serAddr;
    memset(&serAddr,0,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);
    serAddr.sin_port=htons(atoi(argv[2]));
    int ret;
    ret=bind(sock_fd,(struct sockaddr *)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sock_fd,10);//设置socket_fd大小为10
    struct sockaddr_in clientAddr;//用来存客户端的ip地址和端口号
    int addrLen=sizeof(clientAddr);
    int new_fd=accept(sock_fd,(struct sockaddr *)&clientAddr,&addrLen);
    ERROR_CHECK(new_fd,-1,"accept");
    //转换网络字节序为 本机字节序
    printf("ip=%s,port=%d\n",inet_ntoa(clientAddr.sin_addr),
    ntohs(clientAddr.sin_port));
    //读集合
    fd_set rdset;
    char buf[1000];
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(new_fd,&rdset);
        select(new_fd+1,&rdset,NULL,NULL,NULL);
        //如果标准输入可读
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
            memset(buf,0,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));//读取标准输入
            send(new_fd,buf,strlen(buf)-1,0);//数据发送给对方
        }
        if(FD_ISSET(new_fd,&rdset))
        {
            memset(buf,0,sizeof(buf));
            ret=recv(new_fd,buf,sizeof(buf),0);//接收数据
            if(ret==0)
            {
                printf("对方断开了\n");
                break;
            }
            printf("%s\n",buf);
        }
    }
    close(new_fd);
    close(sock_fd);
}