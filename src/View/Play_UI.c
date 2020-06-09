#include<stdio.h>
#include<stdlib.h>
#include "Play_UI.h"
#include "../Service/Play.h"
#include "../Common/common.h"
#include "../Common/List.h"

/* 剧目管理主界面 */
void Play_UI_MgtEntry(void) {
    int id;
    char choice;
    play_list_t list;
    List_Init(list, play_node_t);
    Pagination_t paging;
    paging.pageSize = 10;
    paging.totalRecords = listSize;
    Paging_Locate_FirstPage(list, paging);
    /* 输出剧目信息及菜单项 （暂空）*/
    printf("Please input your choice:");
    scanf("%c", &choice);
    if(choice == 's' || choice == 'S') {
        printf("please input ID:");
        scanf("%d", &id);
        Play_Srv_FetchByID(list, id);
    }
    else if(choice == 'a' || choice == 'A') {
        Play_UI_Add();
    }
    else if(choice == 'u' || choice == 'U') {
        printf("please input ID:");
        scanf("%d", &id);
        Play_UI_Modify(list, id);
        
    }
    else if(choice == 'd' || choice == 'D') {
        printf("please input ID:");
        scanf("%d", &id);
        Play_UI_Delete(list);
    }
    else if(choice == 'p' || choice == 'P') {
        
    }
    else if(choice == 'n' || choice == 'N') {

    }
}

/* 添加剧目 */
int Play_UI_Add(void) {
    int choice;
    int newCount = 0;
    while(1) {
        play_t date;
        printf("请输入剧目ID：");
        scanf("%d", &date.id);
        printf("请输入剧目名称：");
        scanf("%s", date.name);
        printf("请输入剧目ID：");
        scanf("%d", &date.id);
        printf("请输入剧目出品地区：");
        scanf("%s", date.area);
        printf("请输入剧目时长：");
        scanf("%d", &date.duration);
        printf("请输入剧目开始放映日期：");
        scanf("%d %d %d", &date.start_date.year, &date.start_date.month, &date.start_date.day);
        printf("请输入剧目结束放映日期：");
        scanf("%d %d %d", &date.end_date.year, &date.end_date.month, &date.end_date.day);
        printf("请输入建议票价：");
        scanf("%d", &date.price);
        Play_Srv_Add(&date);
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
    int rtn = 0;

}