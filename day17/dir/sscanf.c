#include <stdio.h>

int main(){
    int i=10;
    float f=98.5;
    char c='a';
    char buf[1024]={0};
    //sscanf就是格式化读取字符串，把各种类型的数据变成字符串放到buf中
    sscanf(buf,"%d%f %c",&i,&f,&c); //格式和scanf相同
    printf("%d %5.2f %c\n",i,f,c);
    return 0;
}