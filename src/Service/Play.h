#ifndef PLAY_H_
#define PLAY_H_
#include "../Common/common.h"

/* 获取剧目信息 */
int Play_Srv_FetchAll(play_list_t list);
/* 查询剧目 */
play_list_t Play_Srv_FetchByID(play_list_t list, int id);


#endif