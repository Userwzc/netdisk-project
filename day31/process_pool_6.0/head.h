#include <func.h>

enum workStatus
{
    FREE,
    BUSY
};

typedef struct {
    pid_t pid;
    int status;
    int pipeFd; //子进程的管道对端
}processData_t;

//这个结构体两个成员位置不可以交换
typedef struct {
    int size;
    char buf[1000];
}train_t;

//创建多个子进程
int make_child(processData_t* workerList,int childNum);

//子进程工作
int handleEvent();

//socket,bind,listen的初始化
int tcp_init(char *ip,char *port,int *sock_fd);

//注册监控某个描述符是否可读
int epoll_add(int epfd,int fd);

//发送描述符
int sendFd(int pipeFd,int fd,int);

//接收描述符
int recvFd(int pipeFd,int *fd,int*);

//发送文件
int transFile(int new_fd);