#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int sock_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sock_fd,-1,"socket");
    int ret;
    int reuse=1;
    ret=setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
    ERROR_CHECK(ret,-1,"setsockopt");

    struct sockaddr_in serAddr;
    memset(&serAddr,0,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);
    serAddr.sin_port=htons(atoi(argv[2]));
    ret=bind(sock_fd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sock_fd,10);
    struct sockaddr_in clientAddr;
    int addrLen=sizeof(clientAddr);
    int new_fd=accept(sock_fd,(struct sockaddr*)&clientAddr,&addrLen);
    ERROR_CHECK(new_fd,-1,"accept");
    printf("ip=%s,port=%d\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
    fd_set rdset;
    char buf[100];
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(new_fd,&rdset);
        select(new_fd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
            memset(buf,0,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));
            send(new_fd,buf,sizeof(buf)-1,0);
        }
        if(FD_ISSET(new_fd,&rdset))
        {
            memset(buf,0,sizeof(buf));
            ret=recv(new_fd,buf,sizeof(buf),0);
            if(0==ret)
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