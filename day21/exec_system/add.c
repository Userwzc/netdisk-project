#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    puts(argv[0]);
    int a=atoi(argv[1]);
    int b=atoi(argv[2]);
    printf("sum=%d\n",a+b);
    return 0;
}