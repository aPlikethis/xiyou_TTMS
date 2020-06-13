#ifndef PLAYPERSIST_H_
#define PLAYPERSIST_H_
#include "../Common/common.h"
#include "../Service/Play.h"

/* 添加新剧目 */
int Play_Perst_Insert(play_t *date);
/* 获取剧目信息 */
int Play_Perst_FetchAll(play_list_t list);
/* 根据id查询剧目信息 */
int Play_Perst_SelectByID(int id, play_t *buf);
/* 更新剧目 */
int Play_Perst_Update(const play_t *data);
/* 删除剧目 */
int Play_Perst_DeleteByID(int id);


#endif