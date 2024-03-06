#include <func.h>

int main(int argc,char *argv[]){
    int fdr=open(argv[1],O_RDONLY); //读端
    ERROR_CHECK(fdr,-1,"open");
    printf("fdr=%d\n",fdr);
    char buf[1000]={0};
    int ret=read(fdr,buf,sizeof(buf));
    ERROR_CHECK(ret,-1,"read");
    printf("%s\n",buf);
    return 0;
}