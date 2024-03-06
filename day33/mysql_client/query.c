#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

int main(int argc ,char *argv[])
{
    if(argc!=2)
    {
        printf("error args\n");
        return -1;
    }
    MYSQL *conn;
    MYSQL_RES *res;//结果操作指针
    MYSQL_ROW row;//一行的数据是存在row中间
    const char *server="localhost";
    const char *user="root";
    const char *password="123456";
    const char *database="test";
    char *p="select * from pet where id1=";
    char query[300]={0};
    int id=atoi(argv[1]);
    sprintf(query,"%s%d",p,id);
    puts(query);
    unsigned int t;
    conn=mysql_init(NULL);//要初始化
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
    {
        printf("error connecting to database:%s\n",mysql_error(conn));
        return -1;
    }else{
        printf("connected..\n");
    }
    t=mysql_query(conn,query);//执行sql语句
    if(t)
    {
        printf("error making query:%s\n",mysql_error(conn));//sql的语法出错
    }else{
        printf("Query made...\n");
        res=mysql_use_result(conn); //获取结果
        if(res)
        {
            while((row=mysql_fetch_row(res))!=NULL)
            {
                //printf("num=%d\n",mysql_num_fields(res));//列数
                for(t=0;t<mysql_num_fields(res);t++)
                {
                    printf("%10s ",row[t]);
                }
                printf("\n");
            }
        }else{
            printf("don't find data\n");
        }
    }
    mysql_close(conn);
    return 0;
}