#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    struct in_addr net_ip;//存储ip的网络字节序
    int ret=inet_aton(argv[1],&net_ip);  //执行成功返回1
    if(ret!=1)
    {
        printf("inet_aton failed\n");
    }
    printf("%x\n",net_ip.s_addr);
    printf("ip=%s\n",inet_ntoa(net_ip));
    return 0;
}