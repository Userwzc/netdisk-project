#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int client_fd=socket(AF_INET,SOCK_DGRAM,0);//初始化udp套接字
    ERROR_CHECK(client_fd,-1,"socket");
    int ret;
    //定义结构体，存ip和端口
    struct sockaddr_in serAddr;
    memset(&serAddr,0,sizeof(serAddr));
    serAddr.sin_family=AF_INET;//ipv4
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);//ip
    serAddr.sin_port=htons(atoi(argv[2]));//port

    //客户端就需要先sendto
    ret=sendto(client_fd,"helloworld",10,0,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"sendto");

    char buf[1000]={0};
    recvfrom(client_fd,buf,sizeof(buf),0,NULL,NULL);
    printf("%s\n",buf);
    close(client_fd);
}