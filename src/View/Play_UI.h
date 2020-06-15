#ifndef PLAY_UI_H_
#define PLAY_UI_H_
#include "../Common/common.h"
#include "../Service/Play.h"

/* 管理剧目界面 */
void Play_UI_MgtEntry(void);
/* 初始化剧目信息链表 */
play_list_t List_lnit(void);
/* 添加剧目 */
int Play_UI_Add(void);
/* 删除剧目 */
int Play_UI_DeleteByID(int id);
/* 查询剧目 */
int Plat_UI_Query(int id);
/* 初始化剧目信息链表 */
play_list_t List_lnit(void);
/* 修改剧目 */
int Play_UI_Modify(int id);

#endif