#ifndef PLAY_UI_H_
#define PLAY_UI_H_
#include "../Common/common.h"
#include "../Service/Play.h"

/* �����Ŀ���� */
void Play_UI_MgtEntry(void);
/* ��ʼ����Ŀ��Ϣ���� */
play_list_t List_lnit(void);
/* ��Ӿ�Ŀ */
int Play_UI_Add(void);
/* ɾ����Ŀ */
int Play_UI_DeleteByID(int id);
/* ��ѯ��Ŀ */
int Plat_UI_Query(int id);
/* ��ʼ����Ŀ��Ϣ���� */
play_list_t List_lnit(void);
/* �޸ľ�Ŀ */
int Play_UI_Modify(int id);

#endif