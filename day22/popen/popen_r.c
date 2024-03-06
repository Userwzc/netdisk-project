#include <func.h>

int main()
{
    FILE *fp=popen("./print","r");
    ERROR_CHECK(fp,NULL,"popen");
    char buf[1000]={0};
    fread(buf,sizeof(char),sizeof(buf),fp);
    printf("popen:%s\n",buf);
    pclose(fp);
    return 0;
}