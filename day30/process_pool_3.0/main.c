#include "head.h"

int main(int argc,char *argv[])
{
    if(argc!=4)
    {
        printf("./process_pool IP PORT PROCESS_NUM\n");
        return -1;
    }
    int childNum=atoi(argv[3]);//子进程数目
    processData_t *workerList=(processData_t*)calloc(childNum,sizeof(processData_t));
    make_child(workerList,childNum);//创建子进程
    
    int sock_fd;
    tcp_init(argv[1],argv[2],&sock_fd);

    //注册监控sock_fd;
    int epfd=epoll_create(1);
    epoll_add(epfd,sock_fd);
    //监控每个子进程的管道对端

    int i;
    for(i=0;i<childNum;i++)
    {
        epoll_add(epfd,workerList[i].pipeFd);
    }
    int ready_fd_num,new_fd;
    struct epoll_event *evs=(struct epoll_event *)calloc(childNum+1,sizeof(struct epoll_event));
    struct sockaddr_in clientAddr;
    int addrlen,j,finish_flag;
    while(1)
    {
        ready_fd_num=epoll_wait(epfd,evs,childNum+1,-1);
        for(i=0;i<ready_fd_num;i++)
        {
            if(sock_fd==evs[i].data.fd)
            {
                addrlen=sizeof(clientAddr);
                new_fd=accept(sock_fd,(struct sockaddr*)&clientAddr,&addrlen);
                printf("task coming ip=%s,port=%d\n",inet_ntoa(clientAddr.sin_addr),
                ntohs(clientAddr.sin_port));
                //找到非忙碌的子进程，把任务派给它
                for(j=0;j<childNum;j++)
                {
                    if(workerList[j].status==FREE)
                    {
                        sendFd(workerList[j].pipeFd,new_fd);//发new_fd给对应子进程
                        workerList[j].status=BUSY;
                        printf("%d 派给 %d 子进程\n",new_fd,workerList[j].pid);
                        break;
                    }
                }
                close(new_fd);
            }else{
                for(j=0;j<childNum;j++)
                {
                    if(evs[i].data.fd==workerList[j].pipeFd)
                    {
                        //有子进程通知父进程它完成任务了
                        read(workerList[j].pipeFd,&finish_flag,sizeof(int));//把管道数据读出来
                        workerList[j].status=FREE;//把对应子进程标记为非忙碌
                        printf("%d process finish task\n",workerList[j].pid);
                        break;
                    }
                }
            }
        }
    }
}