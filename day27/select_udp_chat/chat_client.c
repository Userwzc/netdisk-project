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
    ret=sendto(client_fd,"S",1,0,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"sendto");

    char buf[1000]={0};
    fd_set rdset;
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
            //服务器端sendto 给客户端
            sendto(client_fd,buf,strlen(buf)-1,0,(struct sockaddr*)&serAddr,
            sizeof(serAddr));
        }
        if(FD_ISSET(client_fd,&rdset))
        {
            memset(buf,0,sizeof(buf));
            recvfrom(client_fd,buf,sizeof(buf),0,NULL,NULL);//收对方数据
            printf("%s\n",buf);
        }
    }
}