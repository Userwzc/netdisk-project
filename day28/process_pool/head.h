#include <func.h>

enum workStatus{
    FREE,  //空闲
    BUSY  //忙碌
};

typedef struct
{
    pid_t pid;
    int status;
}processData_t;

//创建多个子进程
int make_child(processData_t* workerList,int childNum);

//子进程工作
int handleEvent();

//socket,bind,listen的初始化
int tcp_init(char* ip,char* port,int *sock_fd);