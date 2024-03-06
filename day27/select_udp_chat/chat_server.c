#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int sock_fd=socket(AF_INET,SOCK_DGRAM,0);//初始化udp套接字
    ERROR_CHECK(sock_fd,-1,"sock_fd");
    int ret;
    //定义结构体，存ip和端口
    struct sockaddr_in serAddr;
    memset(&serAddr,0,sizeof(serAddr));
    serAddr.sin_family=AF_INET;//ipv4
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);//ip
    serAddr.sin_port=htons(atoi(argv[2]));//port
  
    ret=bind(sock_fd,(struct sockaddr *)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"bind");
    //先定义一个客户端的socket结构体
    struct sockaddr_in clientAddr;
    int addrLen=sizeof(clientAddr);
    char buf[1000]={0};
    //服务端必须先recvfrom
    ret=recvfrom(sock_fd,buf,sizeof(buf),0,(struct sockaddr*)&clientAddr,&addrLen);
    ERROR_CHECK(ret,-1,"recvfrom");
    printf("recvfrom %s\n",buf);

    fd_set rdset;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(sock_fd,&rdset);
        select(sock_fd+1,&rdset,NULL,NULL,NULL);
        //如果标准输入可读
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
            memset(buf,0,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));//读取标准输入
            //服务器端sendto 给客户端
            sendto(sock_fd,buf,strlen(buf)-1,0,(struct sockaddr*)&clientAddr,
            sizeof(clientAddr));
        }
        if(FD_ISSET(sock_fd,&rdset))
        {
            memset(buf,0,sizeof(buf));
            recvfrom(sock_fd,buf,sizeof(buf),0,NULL,NULL);//收对方数据
            printf("%s\n",buf);
        }
    }
}


