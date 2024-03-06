#include <func.h>

int main(){
    //获取距离1970年1月1号的秒数
    time_t second = time(NULL);
    printf("%ld\n",second);
    //把秒数转为gmtime
    struct tm *p;
    p=gmtime(&second);
    printf("%4d-%02d-%02d %02d:%02d:%02d weekday=%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec,p->tm_wday);
    return 0;
}