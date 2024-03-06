#include <func.h>

int main(int argc,char *argv[]){
    int fdw=open(argv[1],O_WRONLY); //写端
    ERROR_CHECK(fdw,-1,"open");
    printf("fdw=%d\n",fdw);
    int ret=write(fdw,"hello",5);
    ERROR_CHECK(ret,-1,"write");
    return 0;
}
    