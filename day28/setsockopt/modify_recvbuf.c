#include <func.h>

int setNonblock(int fd)
{
    int status;
    status=fcntl(fd,F_GETFL);//获取描述符状态
    status=status|O_NONBLOCK;//增加非阻塞
    int ret;
    ret=fcntl(fd,F_SETFL,status);
    ERROR_CHECK(ret,-1,"fcntl");
}


int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int sock_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sock_fd,-1,"socket");
    struct sockaddr_in serAddr;
    serAddr.sin_family=AF_INET;
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);
    serAddr.sin_port=htons(atoi(argv[2]));
    int ret;
    //地址重用
    int reuse=1;
    ret=setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");

    ret=bind(sock_fd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sock_fd,10);//10是指一瞬间能够放入的客户端连接数
    struct sockaddr_in clientAddr;
    int addrLen=sizeof(clientAddr);
    int new_fd=accept(sock_fd,(struct sockaddr*)&clientAddr,&addrLen);
    ERROR_CHECK(new_fd,-1,"accept");


    //开始使用epoll
    int epfd=epoll_create(1);
    struct epoll_event event;
    event.data.fd=STDIN_FILENO;//要监控的描述符
    event.events=EPOLLIN;//监控读事件
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");

    int recv_bufsize;
    socklen_t buflen=sizeof(int);
    ret=getsockopt(new_fd,SOL_SOCKET,SO_RCVBUF,&recv_bufsize,&buflen);
    printf("recv_bufsize=%u\n",recv_bufsize);
    recv_bufsize=8192;
    ret=setsockopt(new_fd,SOL_SOCKET,SO_RCVBUF,&recv_bufsize,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");

    event.data.fd=new_fd;//要监控的描述符
    event.events=EPOLLIN;//监控读事件
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    struct epoll_event evs[2];
    int ready_fd_num,i;
    char buf[1000]={0};
    char buf_recv[1000];
    while(1)
    {
        ready_fd_num=epoll_wait(epfd,evs,2,-1);
        for(i=0;i<ready_fd_num;i++)
        {
            if(evs[i].data.fd==STDIN_FILENO)
            {
                memset(buf,0,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf));//读取数据
                send(new_fd,buf,strlen(buf)-1,0);//发给对端
            }else if(evs[i].data.fd==new_fd)
            {
                memset(buf_recv,0,sizeof(buf_recv));
                ret=recv(new_fd,buf_recv,sizeof(buf_recv)-1,0);
                if(0==ret)
                {
                    printf("对端断开了\n");
                    goto end;
                }
                printf("%s\n",buf_recv);
            }
        }
    }
end:
    close(new_fd);
    close(sock_fd);
}