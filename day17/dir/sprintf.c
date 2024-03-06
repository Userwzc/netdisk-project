#include <stdio.h>

int main(){
    int i=10;
    float f=98.5;
    char c='a';
    char buf[1024]={0};
    //sprintf就是格式化字符串，把各种类型的数据变成字符串放到buf中
    sprintf(buf,"%d %5.2f %c",i,f,c);
    puts(buf);
    return 0;
}