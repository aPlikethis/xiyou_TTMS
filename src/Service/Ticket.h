#ifndef TICKET_H_
#define TICKET_H_

#include "../Service/Schedule.h"
#include "../Service/Account.h"

//票状态类型定�?

//Ʊ״̬���Ͷ���
typedef enum{
    TICKET_AVL=0,     //����
    TICKET_SOLD=1,    //����
    TICKET_RESV=9     //Ԥ��
}ticket_status_t;


//Ʊʵ���������͵Ķ�������
typedef struct{
    int id;                   //ƱID
    int schedule_id;          //�ݳ��ƻ�ID
    int seat_id;              //��λID
    int price;                //Ʊ��
    ticket_status_t status;   //Ʊ״̬
}ticket_t;


typedef struct ticket_node{
    ticket_t data;
    struct ticket_node *next,*prev;
}ticket_node_t,*ticket_list_t;


//��ʶ����TTMS_SCU_Ticket_Srv_GenBatch
//���ܣ������ݳ�Ʊ
int Ticket_Srv_GenBatch(int schedule_id);


//��ʶ����TTMS_SCU_Ticket_Sry_DeleteBatch
//���ܣ������ݳ��ƻ�IDɾ���ݳ�Ʊ
int Ticket_Srv_DeleteBatch(int schedule_id);


//��ʶ����TTMS_SCU_Ticket_Srv_FetchByID
//���ܣ�����ID��ȡ�ݳ�Ʊ
int Ticket_Srv_FetchByID(int id, ticket_t *buf);

int Ticket_Srv_FetchBySeatID(int seat_id, ticket_t *buf);


//��ʶ����TTMS_SCU_Schedule_Srv_FetchByID
//����: ����ID��ȡ�ݳ��ƻ�
int Schedule_Srv_FetchByID(int id,schedule_t *buf );


int Ticket_Srv_Modify(ticket_t *buf);



#endif
