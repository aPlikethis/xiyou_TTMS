#include<stdio.h>
#include "../Common/List.h"
#include "../Service/Schedule.h"

/* 管理演出计划界面 */
void Schedule_UI_MgtEntry(int play_id) {
    Pagination_t paging;
    schedule_list_t list;
    List_Init(list, schedule_node_t);
    paging.pageSize = 5;
    paging.totalRecords = Schedule_Srv_FechAll(play_id, list);
}