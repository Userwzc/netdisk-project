#include <unistd.h>
#include <stdio.h>
int main()
{
    char path[1024];
    getcwd(path,sizeof(path));    //获取当前路径
    puts(path);
    int ret=chdir("../");
    if(ret!=0)
    {
        perror("chdir");
        return -1;
    }
    puts(getcwd(NULL,0));    //返回当前路径
    return 0;
}