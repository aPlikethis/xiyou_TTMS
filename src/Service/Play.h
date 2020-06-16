#ifndef PLAY_H_
#define PLAY_H_
#include "../Common/common.h"


//8���޸Ŀ�ʼ
/* ��Ŀ���Ͷ��� */
typedef enum {
    PLAY_TYPE_FILM = 1,
    PLAY_TYPE_OPEAR = 2,
    PLAY_TYPE_CONCERT = 3,
}play_type_t;

/* ��Ŀ�ּ����Ͷ��� */
typedef enum {
    PLAY_TYPE_CHILD = 1,
    PLAY_RATE_TEENAGE = 2,
    PLAY_RATE_ADULT = 3
}play_rating_t;

/* �������͵Ķ������� */
//typedef struct {
//    int year;
//    int month;
//    int day;
//}ttms_date_t;
/* ��Ŀʵ���������Ͷ��� */
typedef struct {
    int id;                 //��Ŀid
    char name[31];          //��Ŀ����
    play_type_t type;       //��Ŀ����
    char area[9];           //��Ŀ��Ʒ����
    play_rating_t rating;   //��Ŀ�ȼ�
    int duration;           //ʱ�����Է���Ϊ��λ
    ttms_date_t start_date; //��ʼ��ӳ����
    ttms_date_t end_date;   //��ӳ��������
    int price;              //����Ʊ��

}play_t;

/* ��Ŀ����ڵ㶨�� */
typedef struct play_node {
	play_t data;             //ʵ������
	struct play_node *next;  //���ָ��
	struct play_node *prev;  //ǰ��ָ��
}play_node_t, *play_list_t;


//8���޸Ľ���
/* ��ѯ��Ŀ */
int Play_Srv_FetchByID(int id, play_t *buf);
/* ��Ӿ�Ŀ */
int Play_Srv_Add(play_t *data);
/* ��ȡȫ����Ŀ */
int Play_Srv_FetchAll(play_list_t list);
/* �޸ľ�Ŀ */
int Play_Srv_Modify(const play_t *data);
/* ɾ����Ŀ */
int Play_Srv_DeleteByID(int id);


#endif