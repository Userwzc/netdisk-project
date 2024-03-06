#include <func.h>

int main()
{
    printf("euid=%d,egid=%d\n",geteuid(),getegid());
    return 0;
}