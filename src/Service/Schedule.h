#ifndef SCHEDULE_H_
#define SCHEDULE_H_
/* #include "../Service/Play.h"
#include "../Service/Studio.h" */
#include "../Common/common.h"

/* 演出计划类型定义 */
typedef struct {
    int id;                             //演出计划ID
    int play_id;                        //上映剧目ID
    int studio_id;                      //演出厅ID
    ttms_date_t date;                  //放映日期
    user_time_t time;                  //放映时间
    int seat_count;                     //座位数
} schedule_t;

/* 演出计划节点定义 */
typedef struct schedule_node {
    schedule_t data;
    struct schedule_node *prev;
    struct schedule_node *next;
}schedule_node_t, *schedule_list_t;

/* 查询所有有关id的演出计划信息 */
int Schedule_Srv_SelectByPlayID(int id, schedule_list_t list);

/* 添加演出计划 */
int Schedule_Srv_Add(schedule_t *data);
/* 修改演出计划 */
int Schedule_Srv_Mod(schedule_t *buf);
/* 删除演出计划 */
int Schedule_Srv_Delete(int id);

int Schedule_Srv_SelectByID(int id, schedule_t *data);

/* 根据剧目名称查询演出信息 */
int Schedule_Srv_SelectByName(char name[]);

#endif