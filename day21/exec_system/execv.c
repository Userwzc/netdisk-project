#include <func.h>

int main()
{
    char *const argv[]={"add","3","4",NULL};
    execv("./add",argv);
    printf("you can't see me\n");
    return 0;
}