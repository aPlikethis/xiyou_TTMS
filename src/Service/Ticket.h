#ifndef TICKET_UI_H_
#define TICKET_UI_H_

#include "../Service/Ticket.h"
#include "../Service/Schedule.h"

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



//标识符：TTMS_SCU_Ticket_Sry_DeleteBatch
//功能：根据演出计划ID删除演出�?
void Ticket_Srv_DeleteBatch(int schedule_id);


//标识符：TTMS_SCU_Ticket_Srv_FetchByID
//功能：根据ID获取演出�?
int Ticket_Srv_FetchByID(int id, ticket_t *buf);


//标识符：TTMS_SCU_Schedule_Srv_FetchByID
//功能: 根据ID获取演出计划
int Schedule_Srv_FetchByID(int id,schedule_t *buf );



//查询�?有票信息
//��ѯ����Ʊ��Ϣ
int Ticket_Srv_FetchAll(ticket_list_t list);

//��ʶ����TTMS_SCU_Ticket_Srv_GenBatch
//���ܣ������ݳ�Ʊ
int Ticket_Srv_GenBatch(int schedule_id);


//��ʶ����TTMS_SCU_Ticket_Sry_DeleteBatch
//���ܣ������ݳ��ƻ�IDɾ���ݳ�Ʊ
void Ticket_Srv_DeleteBatch(int schedule_id);


//��ʶ����TTMS_SCU_Ticket_Srv_FetchByID
//���ܣ�����ID��ȡ�ݳ�Ʊ
int Ticket_Srv_FetchByID(int id, ticket_t *buf);


//��ʶ����TTMS_SCU_Schedule_Srv_FetchByID
//����: ����ID��ȡ�ݳ��ƻ�
int Schedule_Srv_FetchByID(int id,schedule_t *buf );

#endif
