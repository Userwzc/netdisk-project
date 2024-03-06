#include <func.h>

void print()
{
    printf("i am print\n"); 
    //调用中间层某个函数
    abort();   //发送abort信号(6)
}

int main()
{
    print();
    printf("i am main\n");
    return 0;
}