#ifndef SCHEDULEPERSIST_H_
#define SCHEDULEPERSIST_H_
#include "../Service/Schedule.h"

/* 查询所有演出计划 */
int Schedule_Perst_FechAll(int id, schedule_list_t list);
/* 添加演出计划 */
int Schedule_Perst_Add(schedule_t *data);
/* 修改演出计划 */
int Schedule_Perst_Update(int id, const schedule_t *buf);
/* 删除演出计划 */
int Schedule_Perst_DeleteByID(int id);

int Schedule_Perst_SelectByID(int id, schedule_t *data);

/* 根据剧目名查询演出计划 */
int Schedule_Perst_SelectByName(char name[]);


#endif