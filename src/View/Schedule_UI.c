#include<stdio.h>
#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "../Persistence/EntityKey_Persist.h"
#include "../Service/Ticket.h"

/* 管理演出计划界面 */
void Schedule_UI_MgtEntry(int play_id) {
    Pagination_t paging;
    schedule_list_t list;
    schedule_node_t *p;
    int i;
    char choice;
    List_Init(list, schedule_node_t);
    paging.pageSize = 5;
    paging.totalRecords = Schedule_Srv_FechAll(play_id, list);
    do {
        system("clear");
        printf("============演出计划===========\n");
        Paging_ViewPage_ForEach(list, paging, schedule_node_t, p, i) {
            
            printf("==========================\n");
            
        }
        printf("==============操作菜单===========\n");
        printf("                                   \n");
        printf("[a]添加新演出计划\n");
        printf("[m]修改演出计划\n");
        printf("[d]删除演出计划\n");
        scanf("%d", &choice);

    }while(choice != 'r' && choice != 'R');
}
/* add */
int Schedule_UI_Add(void) {
    schedule_t data;
    int rtn = 0;
    printf("请输入剧目id：");
    scanf("%d", &data.play_id);
    /*  */
    do {
        printf("请输入演出厅ID:");
        scanf("%d", &data.id);
        /*  */
    }while(data.id != -1);
    if(data.id != -1) {
        printf("=============请输入演出计划数据=================\n");
        printf("\n");
        /*  */
        EntKey_Perst_GetNewKeys(data, 1);
    }
    Schedule_Srv_Add(&data);
    Ticket_Srv_GenBatch(data.id);
}

/* 删除 */
int Sechedule_UI_Del(int id) {
    
}