#include<stdio.h>
#include<stdlib.h>
#include "Play_UI.h"
#include "../Service/Play.h"
#include "../Common/common.h"
#include "../Common/List.h"

/* 剧目管理主界面 */
void Play_UI_MgtEntry(void) {
    while(1) {
        int id, i;
        char choice;
        play_list_t list, f;
        play_node_t *p;
        List_Init(list, play_node_t);
        list->next = NULL;
        Pagination_t paging;
        paging.pageSize = 5;
        paging.offset = 0;
        paging.totalRecords = Play_Srv_FetchAll(list);
        Paging_Locate_FirstPage(list, paging);
        play_t buf; 
        /* 输出剧目信息及菜单项 （暂空）*/
        printf("\n====================================\n");
        printf("           Play information         \n");
        Paging_ViewPage_ForEach(list, paging, play_node_t, p, i) {
            if(p == NULL) {
                break;
            }
            printf("====================================\n");
            printf("ID:                      %d         \n", p->data.id);
            printf("name:                    %s         \n", p->data.name);
            printf("area:                    %s         \n", p->data.area);
            printf("duration:                %d         \n", p->data.duration);
            printf("type:                    %d         \n", p->data.type);
            printf("rating:                  %d         \n", p->data.rating);
            printf("Show start date:         %d-%d-%d   \n", p->data.start_date.year, p->data.start_date.month, p->data.start_date.day);
            printf("End show time:           %d-%d-%d   \n", p->data.end_date.year, p->data.end_date.month, p->data.end_date.day);
            printf("Suggested fare:          %d         \n", p->data.price);
            printf("====================================\n");
        }
        while(list != NULL) {
            f = list;
            list = list->next;
            free(f);
        }
        
        printf("====================================================================================\n");
        printf("                                                                                    \n");
        printf("[s]Query the play    [a]Add a play    [u]Modify the play           [d]Delete a play \n");
        printf("[p]last page                                                       [n]next page     \n");
        printf("====================================================================================\n");
        printf("Please input your choice:");
        scanf("%c", &choice);
        if(choice == 's' || choice == 'S') {
            printf("please input ID:");
            scanf("%d", &id);
            getchar();
            if(Plat_UI_Query(id)) {
                printf("do you want to move to the Schedule UI?(y or n):");
                scanf("%c", &choice);
                getchar();
                if(choice == 'y') {
                    Schedule_UI_MgtEntry(id);
                }
            }
            else {
                printf("Play does not exist\n");
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
            getchar();
            Play_UI_DeleteByID(id);

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
    char flag;
    int newCount = 0;
    while(1) {
        play_t data;
        printf("Please enter the title of the play:");
        scanf("%s", data.name);
        printf("Please enter the stage level:");
        scanf("%d", &data.rating);
        printf("Please enter the type of play:");
        scanf("%d", &data.type);
        printf("Please enter the production area:");
        scanf("%s", data.area);
        printf("Please enter the play duration:");
        scanf("%d", &data.duration);
        printf("Please enter the show start date:");
        scanf("%d %d %d", &data.start_date.year, &data.start_date.month, &data.start_date.day);
        printf("Please enter the end of play date:");
        scanf("%d %d %d", &data.end_date.year, &data.end_date.month, &data.end_date.day);
        printf("Please enter the recommended fare:");
        scanf("%d", &data.price);
        getchar();
        Play_Srv_Add(&data);
        newCount++;
        printf("Do you want to add a new play menu? (enter a or a to confirm, other will be abandoned)\n");
        scanf("%c", &flag);
        getchar();
        if(flag != 'a' || flag != 'A') {
            return newCount;
        }
    }
}

/* 查询剧目 */
int Plat_UI_Query(int id) {
    int rtn = 0;
    play_t data;
    if(Play_Srv_FetchByID(id, &data)) {
        printf("Search succeeded!\n");
        printf("=============================\n");
        printf("       Play information      \n");
        printf("=============================\n");
        printf("name:             %s         \n", data.name);
        printf("area:             %s         \n", data.area);
        printf("duration:         %d         \n", data.duration);
        printf("type:             %d         \n", data.type);
        printf("rating:           %d         \n", data.rating);
        printf("Show start date:  %d-%d-%d   \n", data.start_date.year, data.start_date.month, data.start_date.day);
        printf("End show time:    %d-%d-%d   \n", data.end_date.year, data.end_date.month, data.end_date.day);
        printf("Suggested fare:   %d         \n", data.price);
        printf("=============================\n");
        rtn = 1;
        return rtn;
    }
    else {
        printf("Query failed\n");
    }

}

int Play_UI_Modify(int id) {
    int rtn = 0;
    play_t data;
    if(Play_Srv_FetchByID(id, &data)) {
        printf("=============================\n");
        printf("       Play information      \n");
        printf("=============================\n");
        printf("name:             %s         \n", data.name);
        printf("area:             %s         \n", data.area);
        printf("duration:         %d         \n", data.duration);
        printf("type:             %d         \n", data.type);
        printf("rating:           %d         \n", data.rating);
        printf("Show start date:  %d-%d-%d   \n", data.start_date.year, data.start_date.month, data.start_date.day);
        printf("End show time:    %d-%d-%d   \n", data.end_date.year, data.end_date.month, data.end_date.day);
        printf("Suggested fare:   %d         \n", data.price);
        printf("=============================\n");
    }
    else {
        printf("query error\n");
        return rtn;
    }
    printf("Please enter the play name:");
    scanf("%s", data.name);
    printf("Please enter the stage level:");
    scanf("%d", &data.rating);
    printf("Please enter the type of play:");
    scanf("%d", &data.type);
    printf("Please enter the production area:");
    scanf("%s", data.area);
    printf("Please enter the play duration:");
    scanf("%d", &data.duration);
    printf("Please enter the show start date:");
    scanf("%d %d %d", &data.start_date.year, &data.start_date.month, &data.start_date.day);
    printf("Please enter the end of play date:");
    scanf("%d %d %d", &data.end_date.year, &data.end_date.month, &data.end_date.day);
    printf("Please enter the recommended fare:");
    scanf("%d", &data.price);
    getchar();
    if(Play_Srv_Modify(&data)) {
        rtn = 1;
        printf("sus\n");
        return rtn;
    }
    else {
        printf("detail\n");
        return rtn;
    }

}

/* 删除剧目 */
int Play_UI_DeleteByID(int id) {
    int rtn = 0;

    if(Play_Srv_DeleteByID(id)) {
        printf("succses\n");
        rtn = 1;
        return rtn;
    }
    else {
        printf("defail\n");
        return rtn;
    }

}
