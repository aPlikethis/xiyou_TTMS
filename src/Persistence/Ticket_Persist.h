#ifndef TICKET_UI_H_
#define TICKET_UI_H_

//标识符：TTMS_SCU_Ticket_Perst_Insert
//功能：存储演出票
void Ticket_Perst_Insert(int schedule_id,seat_list_t list);


//标识符:TTMS_SCU_Ticket_Perst_Rem
//功能：根据演出计划ID去除演出票
void Ticket_Perst_Rem(int schedule_id);


//标识符：TTMS_SCU_Ticket_Perst_SelByID
//功能：根据ID在入演出票
int Ticket_Perst_SelBYID(int id, ticket_t *buf);


//标识符：TTMS_SCU_Schedule_Perst_SelectByID
//功能：根据ID载入演出计划
int Schedule_Perst_SelectByID(int id,schedule_t*buf);

#endif