#include "../Common/List.h"
#include "../Common/common.h"

#include "../Service/Ticket.h"
#include "../Service/Seat.h"
// #include "../Service/Sale.h"

#include "../Persistence/Ticket_Persist.h"
#include "../Persistence/Play_Persist.h"
#include "../Persistence/Schedule_Persist.h"
#include <stdio.h>



//��ʶ����TTMS_SCU_Schedule_Srv_FetchByID
//����: ����ID��ȡ�ݳ��ƻ�
int Schedule_Srv_FetchByID(int id,schedule_t*buf )
{
    return Schedule_Perst_SelectByID(id, buf);
}


//��ʶ����TTMS_SCU_Ticket_Srv_GenBatch
//���ܣ������ݳ�Ʊ
int Ticket_Srv_GenBatch(int schedule_id)
{
    int count;
    seat_list_t seat_head;
    seat_head = (seat_list_t *)malloc(sizeof(seat_list_t));
    List_Init(seat_head,seat_node_t);

    schedule_t *need_schedule;
    need_schedule = (schedule_t *)malloc(sizeof(schedule_t));
    Schedule_Srv_FetchByID(schedule_id, need_schedule);
        
    count = Seat_Srv_FetchValidByRoomID(seat_head,need_schedule->studio_id);

    
    if(count==0)
    {
        printf("��λ��Ϣ��ȡʧ�ܣ��޷�����Ʊ");
        return 0;
    }
    else
    {
        count=Ticket_Perst_Insert(schedule_id,seat_head);
        return count;
    }
    
}


//��ʶ����TTMS_SCU_Ticket_Sry_DeleteBatch
//���ܣ������ݳ��ƻ�IDɾ���ݳ�Ʊ
int Ticket_Srv_DeleteBatch(int schedule_id)
{
    return Ticket_Perst_Rem(schedule_id);
}


//��ʶ����TTMS_SCU_Ticket_Srv_FetchByID
//���ܣ�����ID��ȡ�ݳ�Ʊ
int Ticket_Srv_FetchByID(int id, ticket_t *buf)
{
    return Ticket_Perst_SelByID(id,buf);
}


int Ticket_Srv_Modify(ticket_t *buf) {
    return Ticket_Perst_Update(buf);
}

int Ticket_Srv_FetchBySeatID(int seat_id, ticket_t *buf) {
    return Ticket_Perst_SelBySeatID(seat_id, buf);
}

