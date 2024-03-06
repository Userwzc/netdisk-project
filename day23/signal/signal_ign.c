#include <func.h>

int main()
{
    signal(SIGINT,SIG_IGN);
    printf("process begin\n");
    sleep(10);
    printf("sleep over\n");
    signal(SIGINT,SIG_DFL); //恢复默认行为
    while(1);
    return 0;
}