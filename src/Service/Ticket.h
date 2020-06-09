#ifndef Ticket_H_
#define Ticket_H_
#include "Schedule.h"
//票的类型
typedef enum
{
    TICKET_AVL = 0,     //待售
    TICKET_SOLD = 1,    //已售
    TICKET_RESV = 9     //预留
}ticket_status_t;


//票的实体数据类型的定义
typedef struct
{
    int                 id;              //票的ID
    int                 schedule_id;     //演出计划ID
    int                 seat_id;        //座位ID
    int                 price;           //票价
    ticket_status_t     status;          //票状态
}ticket_t;

//票链表节点定义
typedef struct ticket_node{
    ticket_t data;
    struct ticket_node *next, *prev;
}ticket_node_t,*ticket_list_t;

//标识符：TTMS_SCU_Schedule_Srv_FetchByID
//功能: 根据ID获取演出计划
int Schedule_Srv_FetchByID(int  id, schedule_t  *buf);


//标识符：TTMS_SCU_Ticket_Srv_Gen
//功能: 通过持久化层函数来批量增加文件Ticket.dat中的信息。
int Ticket_Srv_GenBatch(int schedule_id , int studio_id);


//标识符：TTMS_SCU_Ticket_Srv_Del
//功能:   根据演出计划的ID删除演出票
int Ticket_Srv_DeleteBatch(int schedule_id);

int Ticket_Srv_StatRevSchID(int schedule_id,int *soldCount);

#endif // Ticket_H_
