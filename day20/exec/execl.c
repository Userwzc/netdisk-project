#include <func.h>

int main()
{
    execl("./add","add","1","2",NULL);
    printf("如果成功，看不到这里\n");
    return 0;
}