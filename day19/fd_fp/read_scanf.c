#include <func.h>
//stdin是指针，STDIN_FILENO是标准输入文件描述符
int main(){
    char buf[1000]={0};
    int ret =read(STDIN_FILENO,buf,sizeof(buf));
    ERROR_CHECK(ret,-1,"read");
    printf("%s",buf);
    return 0;
}