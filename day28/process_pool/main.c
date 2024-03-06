#include "head.h"

int main(int argc,char *argv[])
{
    if(argc!=4)
    {
        printf("./process_pool IP PORT PROCESS_NUM\n");
        return -1;
    }
    int childNum=atoi(argv[3]);//子进程数目
    processData_t *workerList=(processData_t *)calloc(childNum,sizeof(processData_t));
    make_child(workerList,childNum);//创建好了子进程

    int sock_fd;
    tcp_init(argv[1],argv[2],&sock_fd);
    while(1);
}