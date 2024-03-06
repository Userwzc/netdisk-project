#include <func.h>
//stat 获取文件状态 对应ls -l
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int ret;
    struct stat buf;   //为了存储inode信息
    ret=stat(argv[1],&buf);
    ERROR_CHECK(ret,-1,"stat");
    printf("inode =%lu,mode=%d,nlink=%ld,uid=%s,size=%ld,mtime=%s",
    buf.st_ino,buf.st_mode,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,buf.st_size, ctime(&buf.st_mtime));
    return 0;
}