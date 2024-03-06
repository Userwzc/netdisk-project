#include <func.h>

void print()
{
    printf("i am print\n"); //没加\n 打印不出来
    _exit(0);//在子函数中让进程终止
}

int main()
{
    print();
    printf("i am main\n");
    return 0;
}