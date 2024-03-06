#include <func.h>

int main()
{
    unsigned short port=0x1234;
    unsigned short nport;//存转换后的
    nport=htons(port);
    printf("%x\n",nport);//网络字节序
    printf("本机 %x\n",ntohs(nport));//网络字节序变为本机字节序

    return 0;
}