#include <func.h>

typedef struct{
    int tickets;
    pthread_mutex_t mutex;
}Share_t,*pShare_t;



void* sellTicket1(void *p)
{
    pShare_t p1=(pShare_t)p;
    while(p1->tickets>0)
    {
        pthread_mutex_lock(&p1->mutex);//加锁
        printf("Before windows 1 sells tickets, ticketNum = %d\n", p1->tickets);
        p1->tickets--;
        printf("after windows 1 sells tickets, ticketNum = %d\n", p1->tickets);
        pthread_mutex_unlock(&p1->mutex);
    }
    return NULL;
}
//实际上这种写法错误

void* sellTicket2(void *p)
{
    pShare_t p1=(pShare_t)p;
    while(p1->tickets>0)
    {
        pthread_mutex_lock(&p1->mutex);//加锁
        printf("Before windows 2 sells tickets, ticketNum = %d\n", p1->tickets);
        p1->tickets--;
        printf("after windows 2 sells tickets, ticketNum = %d\n", p1->tickets);
        pthread_mutex_unlock(&p1->mutex);
    }
    return NULL;
}


int main()
{
    Share_t t;
    t.tickets=20;//总计有20张票
    int ret;
    ret=pthread_mutex_init(&t.mutex,NULL);
    THREAD_ERR_CHECK(ret,"pthread_mutex_init");
    pthread_t pth_id1,pth_id2;
    pthread_create(&pth_id1,NULL,sellTicket1,&t);
    pthread_create(&pth_id2,NULL,sellTicket2,&t);
    pthread_join(pth_id1,NULL);
    pthread_join(pth_id2,NULL);
    printf("main thread tickets=%d\n",t.tickets);
    return 0;
}