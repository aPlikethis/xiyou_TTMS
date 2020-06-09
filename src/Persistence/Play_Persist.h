#ifndef PLAYPERSIST_H_
#define PLAYPERSIST_H_
#include "../Common/common.h"

/* 添加新剧目 */
int Play_Perst_Insert(play_t *date);
/* 获取剧目信息 */
int Play_Perst_FetchAll(play_list_t list);

#endif