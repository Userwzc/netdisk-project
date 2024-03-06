#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    DIR* dir; //目录指针
    dir = opendir(argv[1]);   //失败返回NULL
    ERROR_CHECK(dir,NULL,"opendir");
    struct dirent *p;
    off_t offset; //记录在磁盘上的偏移位置
    while(p=readdir(dir)) //读取目录
    {
        printf("inode=%lu,filename_len=%u,type=%d,filename=%s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
        if(strcmp(p->d_name,"opendir")==0)
        {
            offset = telldir(dir); //记录偏移
        }
    }
    //通过seekdir回到对应位置
    seekdir(dir,offset);
    p=readdir(dir);
    printf("-----------------\n");
    //ERROR_CHECK(p,NULL,"readdir");
    printf("inode=%lu,filename_len=%u,type=%d,filename=%s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
    closedir(dir);
    return 0;
}