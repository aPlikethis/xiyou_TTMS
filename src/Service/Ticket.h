#ifndef TICKET_H_
#define TICKET_H_

#include "../Service/Schedule.h"
#include "../Service/Account.h"

//绁ㄧ姸鎬佺被鍨嬪畾涔?

//票状态类型定义
typedef enum{
    TICKET_AVL=0,     //待售
    TICKET_SOLD=1,    //已售
    TICKET_RESV=9     //预留
}ticket_status_t;


//票实体数据类型的定义如下
typedef struct{
    int id;                   //票ID
    int schedule_id;          //演出计划ID
    int seat_id;              //座位ID
    int price;                //票价
    ticket_status_t status;   //票状态
}ticket_t;


typedef struct ticket_node{
    ticket_t data;
    struct ticket_node *next,*prev;
}ticket_node_t,*ticket_list_t;


//标识符：TTMS_SCU_Ticket_Srv_GenBatch
//功能：生成演出票
int Ticket_Srv_GenBatch(int schedule_id);


//标识符：TTMS_SCU_Ticket_Sry_DeleteBatch
//功能：根据演出计划ID删除演出票
int Ticket_Srv_DeleteBatch(int schedule_id);


//标识符：TTMS_SCU_Ticket_Srv_FetchByID
//功能：根据ID获取演出票
int Ticket_Srv_FetchByID(int id, ticket_t *buf);

int Ticket_Srv_FetchBySeatID(int seat_id, ticket_t *buf);


//标识符：TTMS_SCU_Schedule_Srv_FetchByID
//功能: 根据ID获取演出计划
int Schedule_Srv_FetchByID(int id,schedule_t *buf );


int Ticket_Srv_Modify(ticket_t *buf);



#endif
