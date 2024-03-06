#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    char *p;
    //使用mmap映射的文件，本身必须有大小,mmap不能改变文件大小
    p=(char*)mmap(NULL,10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,-1,"mmap");
    printf("%s\n",p);
    p[0]='H';
    int ret=munmap(p,10);
    ERROR_CHECK(ret,-1,"munmap");   
    return 0;
}