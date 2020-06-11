#ifndef SCHEDULE_H_
#define SCHEDULE_H_
#include "../Service/Play.h"
#include "../Service/Studio.h"

/* 演出计划类型定义 */
typedef struct {
    play_t play_data;
    studio_t studio_data;
} schedule_t;


/* 演出计划节点定义 */
typedef struct schedule_node {
    schedule_t data;
    struct schedule_node *prev;
    struct schedule_node *next;
}schedule_node_t, *schedule_list_t;

/* 查询所有有关id的演出计划信息 */
int Schedule_Srv_FechAll(int id, schedule_list_t list);
#endif