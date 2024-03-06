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
    //打印客户端ip和地址
    //转换网络字节序为 本机字节序
    printf("ip=%s,port=%d\n",inet_ntoa(clientAddr.sin_addr),
        ntohs(clientAddr.sin_port));
    //服务器端sendto 给客户端
    sendto(sock_fd,"howareyou",9,0,(struct sockaddr*)&clientAddr,sizeof(clientAddr));
    close(sock_fd);
}