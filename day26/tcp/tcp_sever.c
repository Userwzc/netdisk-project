#include <func.h>

int main()
{
    int sever_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sever_fd,-1,"socket");
    struct sockaddr_in serAddr;
    memset(&serAddr,0,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_addr.s_addr=inet_addr("192.168.195.128");
    serAddr.sin_port=htons(2000);
    int ret=bind(sever_fd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sever_fd,10); //设置sever_fd大小为10
    struct sockaddr_in clientAddr;      //用来存客户端的ip地址和端口号
    int addrlen=sizeof(clientAddr);
    int new_fd=accept(sever_fd,(struct sockaddr*)&clientAddr,&addrlen);
    ERROR_CHECK(new_fd,-1,"accept");
    //转换网络字节序为本机字节序
    printf("ip=%s,port=%d\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
    //接收客户端发送的数据
    char buf[1000]={0};
    recv(new_fd,buf,sizeof(buf),0);
    printf("server get %s\n",buf);
    //发送数据给客户端
    send(new_fd,"world",5,0);
    close(new_fd);
    close(sever_fd);
}