#include "head.h"

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int client_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(client_fd,-1,"socket");
    struct sockaddr_in serAddr;
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);
    serAddr.sin_port=htons(atoi(argv[2]));
    serAddr.sin_family=AF_INET;
    int ret;
    ret=connect(client_fd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"connect");
    int control_code;
start:
    printf("1:register,2:login in\n");
    scanf("%d",&control_code);
    user_t user_info;
    if(1==control_code)
    {
        input_user_info(&user_info);
        send_protocol(client_fd,control_code,&user_info,sizeof(user_info));
        recv_protocol(client_fd,&control_code,NULL);
        if(control_code==REGISTER_FAILED)
        {
            goto start;
        }
        printf("register successfully,login already\n");
    }else if(2==control_code)
    {
        input_user_info(&user_info);
        send_protocol(client_fd,control_code,&user_info,sizeof(user_info));
        recv_protocol(client_fd,&control_code,NULL);
        if(LOGIN_SUCCESS==control_code)
        {
            printf("login successfully\n");
        }else{
            printf("login failed\n");
            goto start;
        }
    }else{
        printf("input error\n");
        goto start;
    }
    getchar(); //去除换行符
    //这里是登录后开始发各种请求
    char cmd[1000];
    char parameter[1000]; //命令后可能的参数
    while(1)
    {
        fgets(cmd,sizeof(cmd),stdin);
        cmd[strlen(cmd)-1]=0; //去除\n 
        system("clear"); 
        if(strncmp("cd",cmd,2)==0)
        {
            send_protocol(client_fd,CD,cmd+3,strlen(cmd)-3); //发送数据
            bzero(parameter,sizeof(parameter));
            recv_protocol(client_fd,&control_code,parameter);  //接收成功或失败
            if(SUCCESS==control_code)
            {
                printf("%s\n",parameter);
            }else{
                printf("路径不存在，切换失败\n");
            }
        }
        else if(strncmp("ls",cmd,2)==0)
        {
            send_protocol(client_fd,LS,NULL,0);
            int  recvlen;
            char buf[1000];
            while(1)
            {
                recvn(client_fd,&recvlen,4);
                if(recvlen>0)
                {
                    bzero(buf,sizeof(buf));
                    recvn(client_fd,buf,recvlen);//接收一行打印一行
                    puts(buf); //自带\n 
                }
                else{
                    break;
                }
            }
        }
        else if(strncmp("puts",cmd,4)==0)
        {
            send_protocol(client_fd,PUTS,cmd+5,strlen(cmd)-5);
            //获取文件的md5值并发送
            char md5_str[50]={0};
            Compute_file_md5(cmd+5,md5_str);
            // printf("%s\n",md5_str);
            train_t t;
            strcpy(t.buf,md5_str);
            t.size=strlen(md5_str);
            send(client_fd,&t,t.size+4,0); 
            //判断是否秒传成功
            recv_protocol(client_fd,&control_code,NULL);
            if(SUCCESS==control_code)
            {
                printf("秒传成功\n");
            }else{
                printf("秒传失败,正常上传文件\n");
                transFile(client_fd,cmd+5);
                printf("发送成功\n");
            }
        }
        else if(strncmp("gets",cmd,4)==0)
        {
            off_t seek_pos;
            struct stat file_buf;
            int fd=open(cmd+5,O_RDONLY);
            if(-1==fd)
            {
                printf("文件不存在\n");
                seek_pos=0;
            }
            else{
                fstat(fd,&file_buf); 
                seek_pos=file_buf.st_size;//该文件本地已经下载了一部分
                close(fd);
            }
            char new_cmd[1200]={0};
            sprintf(new_cmd,"%s %ld",cmd,seek_pos);
            send_protocol(client_fd,GETS,new_cmd+5,strlen(new_cmd)-5); 
            recvFile(client_fd,cmd+5);
        }
        else if(strncmp("rm",cmd,2)==0)
        {
            send_protocol(client_fd,RM,cmd+3,strlen(cmd)-3);
            recv_protocol(client_fd,&control_code,NULL);
            if(SUCCESS==control_code)
            {
                 printf("删除成功\n");
            }else{
                printf("目录非空，删除失败\n");
            }
        }
        else if(strncmp("pwd",cmd,3)==0)
        {
            send_protocol(client_fd,PWD,NULL,0);
            bzero(parameter,sizeof(parameter));
            recv_protocol(client_fd,&control_code,parameter);
            printf("%s\n",parameter);
        }
        else if(strncmp("mkdir",cmd,5)==0)
        {
            send_protocol(client_fd,MKDIR,cmd+6,strlen(cmd)-6); //发送文件夹名字  
            recv_protocol(client_fd,&control_code,NULL); //接收成功或失败
            if(control_code==SUCCESS)
            {
                printf("创建成功\n");
            }
            else{
                printf("文件夹已存在，创建失败\n");
            }
        }
        else{
            continue;
        }
    }
    close(client_fd);
    return 0;
}