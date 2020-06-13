#ifndef PLAYPERSIST_H_
#define PLAYPERSIST_H_
#include "../Common/common.h"
#include "../Service/Play.h"

/* ����¾�Ŀ */
int Play_Perst_Insert(play_t *date);
/* ��ȡ��Ŀ��Ϣ */
int Play_Perst_FetchAll(play_list_t list);
/* ����id��ѯ��Ŀ��Ϣ */
int Play_Perst_SelectByID(int id, play_t *buf);
/* ���¾�Ŀ */
int Play_Perst_Update(const play_t *data);
/* ɾ����Ŀ */
int Play_Perst_DeleteByID(int id);


#endif