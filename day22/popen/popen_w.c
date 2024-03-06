#include <func.h>
//模拟OJ
int main()
{
    FILE *fp=popen("./add","w");  //popen拉起来了add进程，fp是管道的写端
    ERROR_CHECK(fp,-1,"popen");
    char buf[1000]="1 2"; //测试用例
    fwrite(buf,sizeof(char),strlen(buf),fp);    //从管道写端写入数据
    pclose(fp);
    return 0;
}