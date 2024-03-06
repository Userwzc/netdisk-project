#include <func.h>
//fopen得到fp,变为fd
int main(){
    FILE *fp=fopen("file","rb+"); //用户态
    ERROR_CHECK(fp,NULL,"fopen");
    int fd=fileno(fp); //拿到文件指针对应的文件描述符
    char buf[1000]={0};
    int ret=read(fd,buf,sizeof(buf));
    ERROR_CHECK(ret,-1,"read");
    printf("%s",buf);
    return 0;
}