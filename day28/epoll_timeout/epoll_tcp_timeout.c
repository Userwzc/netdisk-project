#include <func.h>
//实现客户端长时间不发消息就断开
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
    ret=bind(sock_fd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sock_fd,10);
    struct sockaddr_in clientAddr;



    //开始使用epoll
    int epfd=epoll_create(1);
    struct epoll_event event;
    event.data.fd=STDIN_FILENO;//要监控的描述符
    event.events=EPOLLIN;//监控读事件
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");

    event.data.fd=sock_fd;//要监控的描述符
    event.events=EPOLLIN;//监控读事件
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sock_fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    struct epoll_event evs[3];
    int ready_fd_num,i;
    char buf[1000]={0};
    int new_fd=-1,addrLen;
    //用来控制超时的时间戳
    time_t nowTime,lastTime;
    nowTime=lastTime=time(NULL);//获取当前时间
    int isLogin=0;//没有登录

    while(1)
    {
        ready_fd_num=epoll_wait(epfd,evs,3,1000);//-1代表永久等待
        //超时的时候，ready_fd_num返回0
        if(0==ready_fd_num&&isLogin)
        {
            nowTime=time(NULL);
            if(nowTime-lastTime>5)
            {
                printf("客户端长时间未发信息，服务器给它断开\n");
                //对new_fd解除监控
                event.data.fd=new_fd;//要监控的描述符
                event.events=EPOLLIN;//监控读事件
                ret=epoll_ctl(epfd,EPOLL_CTL_DEL,new_fd,&event);
                ERROR_CHECK(ret,-1,"epoll_ctl");
                close(new_fd);
                isLogin=0;
            }
        }
        for(i=0;i<ready_fd_num;i++)
        {
            lastTime=time(NULL);//客户端连接，或者收取客户端信息
            if(evs[i].data.fd==sock_fd)//sock_fd可读，说明有人连接了
            {
                addrLen=sizeof(clientAddr);
                new_fd=accept(sock_fd,(struct sockaddr*)&clientAddr,&addrLen);
                ERROR_CHECK(new_fd,-1,"accept");
                printf("ip=%s,port=%d connect\n",inet_ntoa(clientAddr.sin_addr),
                    ntohs(clientAddr.sin_port));
                //把new_fd加入监控
                event.data.fd=new_fd;//要监控的描述符
                event.events=EPOLLIN;//监控读事件
                ret=epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
                ERROR_CHECK(ret,-1,"epoll_ctl");
                isLogin=1;
            }
            else if(evs[i].data.fd==STDIN_FILENO)
            {
                memset(buf,0,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf));//读取数据
                send(new_fd,buf,strlen(buf)-1,0);//发给对端
            }else if(evs[i].data.fd==new_fd)
            {
                memset(buf,0,sizeof(buf));
                ret=recv(new_fd,buf,sizeof(buf),0);
                if(0==ret)
                {
                    printf("客户端断开了\n");
                    //对new_fd解除监控
                    event.data.fd=new_fd;//要监控的描述符
                    event.events=EPOLLIN;//监控读事件
                    ret=epoll_ctl(epfd,EPOLL_CTL_DEL,new_fd,&event);
                    ERROR_CHECK(ret,-1,"epoll_ctl");
                    isLogin=0;//客户端自己断开
                    break;
                }
                printf("%s\n",buf);
            }
        }
    }
end:
    close(new_fd);
    close(sock_fd);
}