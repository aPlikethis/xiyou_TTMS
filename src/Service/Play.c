#include "Play.h"
#include "../Persistence/Play_Persist.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Common/common.h"
#include "../Service/Play.h"

/* ��ѯ��Ŀ�����ظþ�Ŀ�Ľڵ�ָ�� */
int Play_Srv_FetchByID(int id, play_t *buf) {
    return Play_Perst_SelectByID(id, buf);
}

/* ��ȡȫ����Ŀ */
int Play_Srv_FetchAll(play_list_t list) {
    return Play_Perst_FetchAll(list);
}

int Play_Srv_Add(play_t *data) {
    return Play_Perst_Insert(data);
}
/* �޸ľ�Ŀ */
int Play_Srv_Modify(const play_t *data) {
    return Play_Perst_Update(data);
}
/* ɾ����Ŀ */
int Play_Srv_DeleteByID(int id) {
    return Play_Perst_DeleteByID(id);
}