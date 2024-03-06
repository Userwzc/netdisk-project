#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int sock_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sock_fd,-1,"socket");
    struct sockaddr_in serAddr;
    serAddr.sin_family=AF_INET;
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);
    serAddr.sin_port=htons(atoni(argv[2]));
    int ret;
    ret=bind(sock_fd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sock_fd,10);
    struct sockaddr_in clientAddr;
    int addrLen=sizeof(clientAddr);
    int new_fd=accept(sock_fd,(struct sockaddr*)&clientAddr,&addrLen);
    ERROR_CHECK(new_fd,-1,"accept");
    signal(SIGPIPE,SIG_IGN);
    char buf[1000]={0};
    int total=0;
    while(1)
    {
        ret=send(new_fd,buf,sizeof(buf),0);
        total+=ret;
        printf("total=%d\n",total);
    }
    close(new_fd);
    close(sock_fd);
}