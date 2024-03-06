#ifndef __HEAD_H__
#define __HEAD_H__
#include <func.h>

//任务字段
typedef struct task_n{
    MYSQL *conn; //子线程自己的连接
    int new_fd;
    int user_id;
    char path[256]; //用户所在路径
    int path_id; //所在目录的id，方便操作数据库
    struct task_n *next;
}task_t;
//任务队列
typedef struct {
    task_t *front;
    task_t *rear;
    pthread_mutex_t mutex;
    int queueSize;
}taskQueue_t;

//线程池
typedef struct {
    pthread_t *thidArr; //存线程id的起始地址
    int threadNum;
    pthread_cond_t cond;//条件变量
    taskQueue_t taskQueue;//任务队列
    int exitFlag; //0表示运行，1表示退出
}factory_t;

//协议字段
typedef struct {
    int size;
    int control_code; //控制码
    char buf[1000];
}protocol_t;

//用户字段
typedef struct {
    char username[16];
    char passwd[16];
}user_t;

typedef struct{
    int size;//火车头，代表火车车厢上放了多少数据
    char buf[1000];//任何数据都可以装
} train_t;

//控制码
enum CONTROL{
    REGISTER,
    LOGIN,
    LS,
    CD,
    PWD,
    MKDIR,
    RM,
    GETS,
    PUTS,
    REGISTER_SUCCESS,
    REGISTER_FAILED,
    LOGIN_SUCCESS,
    LOGIN_FAILED,
    SUCCESS,
    FAILED,
};
int input_user_info(user_t *user);
//发送数据
int send_protocol(int new_fd,int control_code,void *pdata,int send_len);
//循环接收
int recvn(int new_fd,void *pstart,int len);
//接收数据
int recv_protocol(int new_fd,int *control_code,void *pdata);
/*-----数据库操作------*/
//为每个子线程初始化一个连接
int mysql_connect(MYSQL **conn);
//检查用户是否存在
int check_user_exist(MYSQL *conn,char *username);
//把用户信息输入数据库
uint64_t insert_new_user(MYSQL *conn,user_t *pUsr);
//生成随机字符串
void generate_random_string(char *random_string);
//验证用户密码
int check_login(MYSQL *conn,user_t *pUsr);
//发送文件
int transFile(int new_fd,char *file_name);
//接收文件
int recvFile(int new_fd,char *file_name);
//计算MD5值
int Compute_file_md5(char *file_path, char *md5_str);
#endif