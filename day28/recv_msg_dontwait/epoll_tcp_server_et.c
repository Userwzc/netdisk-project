#include <func.h>

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
    listen(sock_fd,10);
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



    event.data.fd=new_fd;//要监控的描述符
    event.events=EPOLLIN|EPOLLET;//监控读事件,采用边沿触发模式
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    struct epoll_event evs[2];
    int ready_fd_num,i;
    char buf[1000]={0};
    char buf_recv[6];
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
                //任务到来，模拟子线程不停读取数据
                while(1)
                {
                    memset(buf_recv,0,sizeof(buf_recv));
                    //客户端发数据比较多，就会执行多次recv
                    ret=recv(new_fd,buf_recv,sizeof(buf_recv)-1,MSG_DONTWAIT);
                    if(0==ret)
                    {
                        printf("对端断开了\n");
                        goto end;
                    }else if(-1==ret)//非阻塞模式下，数据读空，返回-1
                    {
                        printf("\n");
                        break;
                    }
                    printf("%s",buf_recv);
                }
            }
        }
    }
end:
    close(new_fd);
    close(sock_fd);
}