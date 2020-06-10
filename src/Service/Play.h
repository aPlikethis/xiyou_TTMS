#ifndef PLAY_H_
#define PLAY_H_
#include "../Common/common.h"


/* 查询剧目 */
int Play_Srv_FetchByID(int id, play_t *buf);
/* 添加剧目 */
int Play_Srv_Add(play_t *data);
/* 获取全部剧目 */
int Play_Srv_FetchAll(play_list_t list);
/* 修改剧目 */
int Play_Srv_Modify(const play_t *data);
/* 删除剧目 */
int Play_Srv_Delete(int id, play_list_t list);


#endif