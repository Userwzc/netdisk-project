#include <func.h>

int print_dir(char *path,int width){
    DIR* dir; //目录指针
    dir = opendir(path);   //失败返回NULL
    ERROR_CHECK(dir,NULL,"opendir");
    struct dirent *p;
    while(p=readdir(dir)) //读取目录
    {
        if(!strcmp(p->d_name,".")||!strcmp(p->d_name,".."))
        {
            continue;
        }
        printf("%*s%s\n",width,"",p->d_name);
        char path_buf[1024]={0};
        if(p->d_type==4)         //判断是目录就需要继续递归
        {
            //要进行路径拼接
            sprintf(path_buf,"%s/%s",path,p->d_name);
            print_dir(path_buf,width + 4);
        }
    }
    //ERROR_CHECK(p,NULL,"readdir");
    closedir(dir);
}
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    print_dir(argv[1],0);
    return 0;
}