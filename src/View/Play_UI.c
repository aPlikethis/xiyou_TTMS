#include<stdio.h>
#include<stdlib.h>
#include "Play_UI.h"
#include "../Service/Play.h"
#include "../Common/common.h"
#include "../Common/List.h"

int main(void) {
	Play_UI_MgtEntry();
	return 0;
} 
/* 剧目管理主界面 */
void Play_UI_MgtEntry(void) {
    int id, i;
    char choice;
    play_list_t list;
    play_node_t *p;
    List_Init(list, play_node_t);
    Pagination_t paging;
    paging.pageSize = 5;
    paging.totalRecords = Play_Srv_FetchAll(list);
    Paging_Locate_FirstPage(list, paging);
   	play_t *buf; 
    /* 输出剧目信息及菜单项 （暂空）*/
    while(1) {
        printf("==========================\n");
        printf("           剧目信息       \n");
        Paging_ViewPage_ForEach(list, paging, play_node_t, p, i) {
            
            printf("==========================\n");
            printf("名字:           %s         \n", p->data.name);
            printf("出品地区:       %s         \n", p->data.area);
            printf("时长：          %d         \n", p->data.duration);
            printf("开始放映日期：  %d-%d-%d   \n", p->data.start_date.year, p->data.start_date.month, p->data.start_date.day);
            printf("结束放映时间：  %d-%d-%d    \n", p->data.end_date.year, p->data.end_date.month, p->data.end_date.day);
            printf("建议票价:       %d         \n", p->data.price);
            printf("===========================\n");
        }
        printf("========================================================\n");
        printf("                                                        \n");
        printf("[s]查询剧目    [a]添加剧目    [u]修改剧目     [d]删除剧目 \n");
        printf("[p]上一页                                    [n]下一页   \n");
        printf("========================================================\n");
        printf("Please input your choice:");
        scanf("%c", &choice);
        if(choice == 's' || choice == 'S') {
            printf("please input ID:");
            scanf("%d", &id);
            if(Play_Srv_FetchByID(id, buf)) {
                /* Schedule_UI_MgtEn; */
            }
            else {
                printf("剧目不存在\n");
            }
        }
        else if(choice == 'a' || choice == 'A') {
            Play_UI_Add();
        }
        else if(choice == 'u' || choice == 'U') {
            printf("please input ID:");
            scanf("%d", &id);
            Play_UI_Modify(id);
            
        }
        else if(choice == 'd' || choice == 'D') {
            printf("please input ID:");
            scanf("%d", &id);
            Play_UI_Delete(list);
        }
        else if(choice == 'p' || choice == 'P') {
            Paging_Locate_OffsetPage(list, paging, 1, play_node_t);
        }
        else if(choice == 'n' || choice == 'N') {
            Paging_Locate_OffsetPage(list, paging, -1, play_node_t);
        }
    }
}

/* 添加剧目 */
int Play_UI_Add(void) {
    int choice;
    int newCount = 0;
    while(1) {
        play_t data;
        printf("请输入剧目ID：");
        scanf("%d", &data.id);
        printf("请输入剧目名称：");
        scanf("%s", data.name);
        printf("请输入剧目ID：");
        scanf("%d", &data.id);
        printf("请输入剧目出品地区：");
        scanf("%s", data.area);
        printf("请输入剧目时长：");
        scanf("%d", &data.duration);
        printf("请输入剧目开始放映日期：");
        scanf("%d %d %d", &data.start_date.year, &data.start_date.month, &data.start_date.day);
        printf("请输入剧目结束放映日期：");
        scanf("%d %d %d", &data.end_date.year, &data.end_date.month, &data.end_date.day);
        printf("请输入建议票价：");
        scanf("%d", &data.price);
        Play_Srv_Add(&data);
        newCount++;
        printf("是否增加新剧目菜单?(输入a或A确定，其他放弃)");
        scanf("%d", &choice);
        if(choice != 'a' || choice != 'A') {
            return newCount;
        }
    }
}

/* 查询剧目 */
int Plat_UI_Query(void) {
    int id, rtn = 0;
    play_t data;
    scanf("%d", &id);
    if(Play_Srv_FetchByID(id, &data)) {
        printf("查寻成功!\n");
        rtn = 1;
        return rtn;
    }
    else {
        printf("查询失败了\n");
    }

}

int Play_UI_Modify(int id) {
    int rtn = 0;
    play_t data;
    if(Play_Srv_FetchByID(id, &data)) {
        printf("==========================\n");
        printf("           剧目信息        \n");
        printf("==========================\n");
        printf("名字:           %s         \n");
        printf("出品地区:       %s         \n");
        printf("时长：          %d         \n");
        printf("开始放映日期：  %d-%d-%d   \n");
        printf("结束放映时间：  %d-%d-%d    \n");
        printf("建议票价:       %d         \n");
        printf("===========================\n");
    }
    else {
        printf("查询错误\n");
        return rtn;
    }
    printf("请输入剧目ID：");
    scanf("%d", &data.id);
    printf("请输入剧目名称：");
    scanf("%s", data.name);
    printf("请输入剧目ID：");
    scanf("%d", &data.id);
    printf("请输入剧目出品地区：");
    scanf("%s", data.area);
    printf("请输入剧目时长：");
    scanf("%d", &data.duration);
    printf("请输入剧目开始放映日期：");
    scanf("%d %d %d", &data.start_date.year, &data.start_date.month, &data.start_date.day);
    printf("请输入剧目结束放映日期：");
    scanf("%d %d %d", &data.end_date.year, &data.end_date.month, &data.end_date.day);
    printf("请输入建议票价：");
    scanf("%d", &data.price);
    if(Play_Srv_Modify(&data)) {
        rtn = 1;
        printf("修改成功\n");
        return rtn;
    }
    else {
        printf("修改失败\n");
        return rtn;
    }

}

/* 删除剧目 */
int Play_UI_Delete(play_list_t list) {
    int rtn = 0;
    int id;
    scanf("%d", &id);
    if(Play_Srv_Delete(id, list)) {
        printf("删除成功！\n");
        rtn = 1;
        return rtn;
    }
    else {
        printf("删除失败！\n");
        return rtn;
    }

}
