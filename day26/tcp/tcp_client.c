#include <func.h>

int main()
{
    int client_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(client_fd,-1,"socket");
    struct sockaddr_in serAddr; //定义结构体，存储ip和端口号
    memset(&serAddr,0,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_addr.s_addr=inet_addr("192.168.195.128");
    serAddr.sin_port=htons(2000);
    int ret=connect(client_fd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"connet");
    send(client_fd,"hello",5,0); //往client发送数据
    //接受服务器发来的数据
    char buf[1000]={0};
    recv(client_fd,buf,sizeof(buf),0);//接受缓存区为空，会阻塞
    printf("client gets=%s\n",buf);
    close(client_fd);
}