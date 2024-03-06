#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    struct hostent* pHost = gethostbyname(argv[1]);
    ERROR_CHECK(pHost,NULL,"gethostbyname");
    printf("hname=%s\n",pHost->h_name);//真实主机名
    int i;
    for(i=0;pHost->h_aliases[i]!=NULL;i++)
    {
        printf("%s\n",pHost->h_aliases[i]);
    }
    printf("addrtype=%d\n",pHost->h_addrtype);//地址类型
    printf("addrlength=%d\n",pHost->h_length);//地址长度
    char buf[128]={0};
    for(i=0;pHost->h_addr_list[i] != NULL;i++){
        memset(buf,0,sizeof(buf));
        inet_ntop(pHost->h_addrtype,pHost->h_addr_list[i],buf,sizeof(buf));
        printf("addr=%s\n",buf);
    }
    return 0;
}