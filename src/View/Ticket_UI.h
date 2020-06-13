#ifndef TICKET_UI_H_
#define TICKET_UI_H_

//标识符：TTMS_SCU_Ticket_UI_MgtEnt
//功能：显示与参数对应的演出计划信息
void Ticket_UI_MgtEntry(int schedule_id);


//标识符：TTMS_SCU_Ticket_UI_Qry
//功能：查询演出票界面
void Ticket_UI_Query(void);


//标识符：TTMS_SCU_Ticket_UI_ShowTicket
//功能：显示演出票界面
int Ticket_UI_ShowTicket(int ticket_id);

#endif