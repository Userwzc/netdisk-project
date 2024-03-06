#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2); //检查传参
    int ret= mkdir(argv[1],0777);       //需要减去umask 得到775
    ERROR_CHECK(ret,-1,"mkdir");
    return 0;
}