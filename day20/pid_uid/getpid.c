#include <func.h>

int main()
{
    printf("pid=%d,parent pid=%d\n",getpid(),getppid());
    while(1);
    return 0;
}