#include "head.h"

int input_user_info(user_t *user)
{
    printf("username\n");
    scanf("%s",user->username);
    printf("passwd\n");
    scanf("%s",user->passwd);
    return 0;
}


int send_protocol(int new_fd,int control_code,void *pdata,int send_len)
{
    protocol_t t;
    int ret;
    t.size=send_len;
    t.control_code=control_code;
    if(pdata)
    {
        memcpy(t.buf,pdata,send_len);
    }
    ret=send(new_fd,&t,8+t.size,0);
    ERROR_CHECK(ret,-1,"send");
    return 0;
}

int recvn(int new_fd,void *pstart,int len)
{
    int total=0,ret;
    char *p=(char *)pstart;
    while(total<len)
    {
        ret=recv(new_fd,p+total,len-total,0);
        ERROR_CHECK(ret,-1,"recv");
        if(0==ret)
        {
            printf("对方断开了\n");
            return -1;
        }
        total+=ret;
    }
    return 0;
}

int recv_protocol(int new_fd,int *control_code,void *pdata)
{
    int recvlen;
    recvn(new_fd,&recvlen,4);
    recvn(new_fd,control_code,4);
    recvn(new_fd,pdata,recvlen);
    return 0;
}


int check_user_exist(MYSQL *conn,char *username)
{
    unsigned int t;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int return_flag;//0表示未查到，1表示查到
    char *p="select user_name from users where user_name='";
    char query[300]={0};
    sprintf(query,"%s%s'",p,username);
    puts(query);
    t=mysql_query(conn,query);
    if(t)
    {
        printf("Error making query:%s\n",mysql_error(conn));
    }else{
        res=mysql_use_result(conn);
        if(res)
        {
            row=mysql_fetch_row(res);
            if(NULL==row)
            {
                return_flag=0;
            }else{
                return_flag=1;
            }
        }
        mysql_free_result(res);
    }
    return return_flag;
}

void generate_random_string(char *random_string) 
{
    char *charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int i;

    srand(time(NULL)); // 设置种子
    
    for (i = 3; i < 19; ++i) {
        random_string[i] = charset[rand() % (strlen(charset) - 1)];
    }

    random_string[19] = '\0'; // 添加字符串结尾

}


uint64_t insert_new_user(MYSQL *conn,user_t *pUsr)
{
    unsigned t;
    char salt[20]="$6$";
    generate_random_string(salt);//往后拼接16个随机salt
    struct crypt_data cr_data;
    crypt_r(pUsr->passwd,salt,&cr_data);//得到密文
    char *psql="insert into users values(0,'";
    char query[1000]={0};
    sprintf(query,"%s%s','%s','%s')",psql,pUsr->username,salt,cr_data.output);
    puts(query);
    t=mysql_query(conn,query);
    if(t)
    {
        printf("error making query:%s\n",mysql_error(conn));
        return 0;
    }else{
        // return mysql_affected_rows(conn);
        return 1;
    }
}

int check_login(MYSQL *conn,user_t *pUsr)
{
	unsigned int t;
	int login_flag;
	MYSQL_RES *res;//结果操作指针
	MYSQL_ROW row;//一行的数据是存在row中间

	struct crypt_data cr_data;
	

	char *psql="SELECT salt, ciphertext FROM users WHERE user_name = '";
	char query[1000]={0};
	sprintf(query,"%s%s'",psql,pUsr->username);
    puts(query);
	t=mysql_query(conn,query);//执行sql语句
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));//sql的语法出错
	}else{
		res=mysql_use_result(conn);//获取结果
		if(res)
		{
			row=mysql_fetch_row(res);
			if(row)
			{
				// printf("%s  %s\n",row[0],row[1]);
				crypt_r(pUsr->passwd,row[0],&cr_data);//row[0]是salt,得到密文
				// puts(cr_data.output);
				if(!strcmp(cr_data.output,row[1]))
				{
					login_flag=1;//登录成功
				}else{
					login_flag=0;//有用户名，密码不对
				}
			}
			else{
				login_flag=0;//没有用户名
			}
		}
		mysql_free_result(res);
	}
	return login_flag;
}

//发送文件
int transFile(int new_fd,char *file_name)
{
    train_t t;
    //先打开文件
    int fd=open(file_name,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");

    //发送 文件大小给对端
    struct stat file_buf;
    fstat(fd,&file_buf);
    t.size=sizeof(file_buf.st_size);
    memcpy(t.buf,&file_buf.st_size,sizeof(file_buf.st_size));
    send(new_fd,&t,4+t.size,0);

    //通过sendfile发送文件内容
    long ret=sendfile(new_fd,fd,NULL,file_buf.st_size);
    ERROR_CHECK(ret,-1,"sendfile");
end:
    close(fd);
    return 0;
}

//接收文件
int recvFile(int new_fd,char *file_name)
{
    int fd=open(file_name,O_RDWR|O_CREAT|O_APPEND,0666);
    ERROR_CHECK(fd,-1,"open");
    //接文件大小
    off_t fileSize;//偏移之后的总长度
    int recvLen;
    recvn(new_fd,&recvLen,4);
    recvn(new_fd,&fileSize,recvLen);

    struct timeval start,end;
    gettimeofday(&start,NULL);

    off_t downLoadSize=0;
    off_t lastSize=0;
    off_t slice=fileSize/100;//每百分之一

    char buf[1000]={0};
    //接文件内容,1000的整数倍
    while(fileSize-downLoadSize>=1000)
    {
        recvn(new_fd,buf,1000);
        write(fd,buf,1000);
        downLoadSize+=1000;
        if(downLoadSize-lastSize>slice)
        {
            printf("%5.2lf%%\r",100.0*downLoadSize/fileSize);
            fflush(stdout);
            lastSize=downLoadSize;
        }
    }
    recvn(new_fd,buf,fileSize-downLoadSize);
    write(fd,buf,fileSize-downLoadSize);
    gettimeofday(&end,NULL);
    //统计下载总时间
    printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    close(fd);//关闭文件
    return 0;
}




