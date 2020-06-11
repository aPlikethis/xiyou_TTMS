#ifndef SCHEDULEUI_H_
#define SCHEDULEUI_H_
#include "../Service/Schedule.h"
#include <stdio.h>

/* 管理界面 */
void Schedule_UI_MgtEntry(int Play_id);
/* 添加演出计划 */
int Schedule_UI_Add(void);
/* 修改演出计划 */
int Schedule_UI_Mod(int id);
/* 删除演出计划 */
int Schedule_UI_Del(schedule_list_t list);
#endif