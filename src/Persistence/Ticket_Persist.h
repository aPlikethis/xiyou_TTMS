#ifndef TICKETPERSIST_H_
#define TICKETPERSIST_H_
#include "../Service/Seat.h"
#include "../Service/Ticket.h"
#include "../Service/Schedule.h"

//��ʶ����TTMS_SCU_Ticket_Perst_Insert
//���ܣ��洢�ݳ�Ʊ
int Ticket_Perst_Insert(int schedule_id,seat_list_t list);


//��ʶ��:TTMS_SCU_Ticket_Perst_Rem
//���ܣ������ݳ��ƻ�IDȥ���ݳ�Ʊ
int Ticket_Perst_Rem(int schedule_id);


//��ʶ����TTMS_SCU_Ticket_Perst_SelByID
//���ܣ�����ID�������ݳ�Ʊ
int Ticket_Perst_SelByID(int id, ticket_t *buf);


//��ʶ����TTMS_SCU_Schedule_Perst_SelectByID
//���ܣ�����ID�����ݳ��ƻ�
int Schedule_Perst_SelectByID(int id,schedule_t*buf);

//��ѯ����Ʊ��Ϣ
//int Ticket_Perst_FetchAll(ticket_list_t list);


int Ticket_Perst_Update(ticket_t *buf);

int Ticket_Perst_SelBySeatID(int seat_id, ticket_t *buf);


#endif