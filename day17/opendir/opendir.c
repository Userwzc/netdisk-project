#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    DIR* dir; //目录指针
    dir = opendir(argv[1]);   //失败返回NULL
    ERROR_CHECK(dir,NULL,"opendir");
    struct dirent *p;
    while(p=readdir(dir)) //读取目录
    {
        printf("inode=%lu,filename_len=%u,type=%d,filename=%s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
    }
    //ERROR_CHECK(p,NULL,"readdir");
    closedir(dir);
    return 0;
}