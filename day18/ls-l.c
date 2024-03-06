#include <func.h>
void print_permissions(mode_t mode) {
    // 使用位掩码获取文件类型
    switch (mode & __S_IFMT) {
        case __S_IFREG:
            printf("-");
            break;
        case __S_IFDIR:
            printf("d");
            break;
        case __S_IFLNK:
            printf("l");
            break;
        case __S_IFCHR:
            printf("c");
            break;
        case __S_IFBLK:
            printf("b");
            break;
        case __S_IFIFO:
            printf("p");
            break;
        case __S_IFSOCK:
            printf("s");
            break;
    }
    // 输出用户权限
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");

    // 输出组权限
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");

    // 输出其他用户权限
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}
//stat 获取文件状态 对应ls -l
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    DIR* dir; //目录指针
    dir = opendir(argv[1]);   //失败返回NULL
    ERROR_CHECK(dir,NULL,"opendir");
    struct dirent *p;
    int ret;
    struct stat buf;   //为了存储inode信息
    char path[1024]={0};
    while(p=readdir(dir)) //读取目录
    {
        if(!strcmp(p->d_name,".")||!strcmp(p->d_name,".."))
        {
            continue;
        }
        sprintf(path,"%s/%s",argv[1],p->d_name);
        ret=stat(path,&buf);
        ERROR_CHECK(ret,-1,"stat");
        print_permissions(buf.st_mode);
        printf(" %ld %s %s %5ld %s",buf.st_nlink,getpwuid(buf.st_uid)->pw_name,
        getgrgid(buf.st_gid)->gr_name, buf.st_size, ctime(&buf.st_mtime) + 4);
    }
    closedir(dir);
    return 0;
}