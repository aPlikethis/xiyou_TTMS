#include<stdio.h>
#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "../Persistence/EntityKey_Persist.h"
#include "../Service/Ticket.h"
#include "../View/Ticket_UI.h"

/* 管理演出计划界面 */
void Schedule_UI_MgtEntry(int play_id) {
    Pagination_t paging;
    schedule_list_t list;
    schedule_node_t *p;
    int i;
    char choice;
    List_Init(list, schedule_node_t);
    paging.offset = 0;
    paging.pageSize = 5;
    paging.totalRecords = Schedule_Srv_SelectByPlayID(play_id, list);
    do {
        system("clear");
        printf("============演出计划===========\n");
        Paging_ViewPage_ForEach(list, paging, schedule_node_t, p, i) {
            
            printf("==========================\n");
            /*  */
            
        }
        printf("==============操作菜单===========\n");
        printf("                                   \n");
        printf("[a]添加新演出计划\n");
        printf("[m]修改演出计划\n");
        printf("[d]删除演出计划\n");
        printf("[r]退出");
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
        data.id = EntKey_Perst_GetNewKeys(&data, 1);
    }
    Schedule_Srv_Add(&data);
    Ticket_UI_MgtEntry(data.id);
}

/* 删除 */
int Schedule_UI_Del(int id) {
    int rtn = 0;
    if(Schedule_Srv_Delete(id)) {
        printf("删除成功！\n");
        rtn = 1;
        return rtn;
    }
    else {
        printf("删除失败！\n");
        return rtn;
    }
}
/* mod */
int Schedule_UI_Mod(int id) {
    int rtn = 0;
    schedule_t data;
    if(Schedule_Srv_SelectByID(id, &data)) {
        printf("=========演出计划信息=========\n");
        printf("                             \n");
        printf("演出计划ID：                %d\n",data.id);
        printf("剧目ID：                    %d\n",data.play_id);
        printf("演出厅ID：                  %d\n",data.studio_id);
        printf("放映日期：            %d-%d-%d\n",data.date.year, data.date.month, data.date.day);
        printf("放映时间：            %d-%d-%d\n",data.time.hour, data.time.minute, data.time.second);
        printf("座位数：                    %d\n",data.seat_count);
        printf("==============================\n");
        printf("请输入要修改的信息：\n");
        printf("请输入剧目ID:");
        scanf("%d", &data.play_id);
        /*  */
        printf("");
        scanf("%d", &data.studio_id);
        printf("");
        scanf("%d-%d-%d", &data.date.year, &data.date.month, &data.date.day);

        if(Schedule_Srv_Mod(&data)) {
            printf("修改成功\n");
            rtn = 1;
            return rtn;
        }
        else {
            printf("修改失败\n");
            return rtn;
        }
    }
    else {
        printf("没有找到\n");
        return rtn;
    }
}

int Schedule_UI_Query(void) {
    char name[40];
    printf("please input play name:");
    scanf("%s", name);
    Schedule_Srv_SelectByName(name);
}