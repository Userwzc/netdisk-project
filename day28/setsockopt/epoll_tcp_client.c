#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int client_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(client_fd,-1,"socket");
    struct sockaddr_in serAddr;
    serAddr.sin_family=AF_INET;
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);
    serAddr.sin_port=htons(atoi(argv[2]));
    int ret;
    ret=connect(client_fd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"connect");


    //开始使用epoll
    int epfd=epoll_create(1);
    struct epoll_event event;
    event.data.fd=STDIN_FILENO;//要监控的描述符
    event.events=EPOLLIN;//监控读事件
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");

    event.data.fd=client_fd;//要监控的描述符
    event.events=EPOLLIN;//监控读事件
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,client_fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    struct epoll_event evs[2];
    int ready_fd_num,i;
    char buf[1000]={0};
    while(1)
    {
        ready_fd_num=epoll_wait(epfd,evs,2,-1);
        for(i=0;i<ready_fd_num;i++)
        {
            if(evs[i].data.fd==STDIN_FILENO)
            {
                memset(buf,0,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf));//读取数据
                send(client_fd,buf,strlen(buf)-1,0);//发给对端
            }else if(evs[i].data.fd==client_fd)
            {
                memset(buf,0,sizeof(buf));
                ret=recv(client_fd,buf,sizeof(buf),0);
                if(0==ret)
                {
                    printf("对端断开了\n");
                    goto end;
                }
                printf("%s\n",buf);
            }
        }
    }
end:
    close(client_fd);
}