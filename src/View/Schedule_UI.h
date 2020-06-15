#ifndef SCHEDULEUI_H_
#define SCHEDULEUI_H_
#include <stdio.h>
#include "../Service/Schedule.h"


/* 管理界面 */
void Schedule_UI_MgtEntry(int Play_id);
/* 添加演出计划 */
int Schedule_UI_Add(void);
/* 修改演出计划 */
int Schedule_UI_Mod(void);
/* 删除演出计划 */
int Schedule_UI_Del(void);
/* 查询 */
int Schedule_UI_Query(void);


#endif