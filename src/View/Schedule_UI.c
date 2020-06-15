#include <stdio.h>
#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "Schedule_UI.h"
#include "../Persistence/Schedule_Persist.h"
#include "../Persistence/EntityKey_Persist.h"
#include "../Service/Studio.h"
#include "../Service/Play.h"
/* #include "../Service/Ticket.h"
#include "../View/Ticket_UI.h" */

/* 管理演出计划界面 */
void Schedule_UI_MgtEntry(int play_id) {
    char choice;
    do {
        Pagination_t paging;
        schedule_list_t list, f;
        schedule_node_t *p;
        int i;

        List_Init(list, schedule_node_t);
        list->next = NULL;
        paging.offset = 0;
        paging.pageSize = 5;
        paging.totalRecords = Schedule_Srv_SelectByPlayID(play_id, list);
        Paging_Locate_FirstPage(list, paging);

        printf("============Performance plan===========\n");
        Paging_ViewPage_ForEach(list, paging, schedule_node_t, p, i) {
            if(p == NULL) {
                break;
            }
            
            printf("=======================================\n");
            printf("======Performance plan information=====\n");
            printf("                                       \n");
            printf("Performance plan ID:          %d       \n", p->data.id);
            printf("Play ID:                      %d       \n", p->data.play_id);
            printf("Studio ID:                    %d       \n", p->data.studio_id);
            printf("Screprintening date:          %d-%d-%d \n", p->data.date.year, p->data.date.month, p->data.date.day);
            printf("Screening time:               %d-%d-%d \n", p->data.time.hour, p->data.time.minute, p->data.time.second);
            printf("Seat count:                   %d       \n", p->data.seat_count);
            printf("=======================================\n");
        }
        while(list != NULL) {
            f = list;
            list = list->next;
            free(f);
        }

        printf("                                       \n");
        printf("==============Operation menu===========\n");
        printf("                                   \n");
        printf("[a]Add a new show plan\n");
        printf("[u]Modify performance plan\n");
        printf("[d]Delete show plan\n");
        printf("[r]drop out\n");
        scanf("%c", &choice);
        getchar();
        if(choice == 'a') {
            if(Schedule_UI_Add()) {
                printf("Added successfully\n");
            }
            else {
                printf("add failed\n");
            }
        }
        if(choice == 'u') {
            if(Schedule_UI_Mod()) {
                printf("Successfully modified\n");
            }
            else {
                printf("fail to edit\n");
            }
        }
        if(choice == 'd') {
            if(Schedule_UI_Del()) {
                printf("successfully deleted\n");
            }
            else {
                printf("failed to delete\n");
            }
        }

    }while(choice != 'r' && choice != 'R');
}
/* add */
int Schedule_UI_Add(void) {
    schedule_t data;
    play_t play_data;
    studio_t studio_data;
    int rtn = 0;
    printf("=============Please enter performance plan data=================\n");
    printf("\n");
    do {
        printf("Please enter the play id:");
        scanf("%d", &data.play_id);
        if(Play_Srv_FetchByID(data.play_id, &play_data)) {
            break;
        }
        else {
            printf("Please enter again\n");
        }
    }while(1);
    
    do {                    
        printf("Please enter the studio ID:");
        scanf("%d", &data.studio_id);
         if(Studio_Srv_FetchByID(data.studio_id, &studio_data)) {
            break;
        }
        else {
            printf("Please enter again\n");
        } 
    }while(1);
    printf("Please enter the performance date:");
    scanf("%d %d %d", &data.date.year, &data.date.month, &data.date.day);
    printf("Please enter the show time: ");
    scanf("%d %d %d", &data.time.hour, &data.time.minute, &data.time.second);
    getchar();
    if(Schedule_Srv_Add(&data)) {
        rtn = 1;
    }
//    Ticket_UI_MgtEntry(data.id);
    return rtn;
}

/* 删除 */
int Schedule_UI_Del(void) {
    int id, rtn = 0;
    printf("Please enter the show plan ID:");
    scanf("%d", &id);
    getchar();
    
    if(Schedule_Srv_Delete(id)) {
        rtn = 1;
        return rtn;
    }
    else {
        return rtn;
    }
}


/* mod */
int Schedule_UI_Mod(void) {
    int id, rtn = 0;
    printf("Please enter the show plan ID:");
    scanf("%d", &id);
    schedule_t data;
    play_t play_data;
    studio_t studio_data;
    if(Schedule_Srv_SelectByID(id, &data)) {
        printf("=======================================\n");
        printf("======Performance plan information=====\n");
        printf("                                       \n");
        printf("Performance plan ID:          %d       \n", data.id);
        printf("Play ID:                      %d       \n", data.play_id);
        printf("Studio ID:                    %d       \n", data.studio_id);
        printf("Screening date:               %d-%d-%d \n", data.date.year, data.date.month, data.date.day);
        printf("Screening time:               %d-%d-%d \n", data.time.hour, data.time.minute, data.time.second);
        printf("Seat count:                   %d       \n", data.seat_count);
        printf("=======================================\n");
        printf("==Please enter performance plan data===\n");
        printf("\n");
        do {
            printf("Please enter the play id:");
            scanf("%d", &data.play_id);
            if(Play_Srv_FechByID(data.play_id, &play_data)) {
                break;
            }
            else {
                printf("can not found Play! Please enter again\n");
            }
        }while(1);
    
        do {
        printf("Please enter the hall ID:");
        scanf("%d", &data.studio_id);
            if(Studio_Srv_FechByID(data.studio_id, &studio_data)) {
                break;
            }
            else {
                printf("can not found Studio! Please enter again\n");
            }
        }while(1);
    printf("Please enter the performance date:");
    scanf("%d %d %d", &data.date.year, &data.date.month, &data.date.day);
    printf("Please enter the show time: ");
    scanf("%d %d %d", &data.time.hour, &data.time.minute, &data.time.second);
    getchar();

        if(Schedule_Srv_Mod(&data)) {
            rtn = 1;
            return rtn;
        }
        else {
            return rtn;
        }
    }
    else {
        printf("could not find it\n");
        return rtn;
    }
}

int Schedule_UI_Query(void) {
    char name[31];
    char flag;
    do {
        printf("please input play name:");
        scanf("%s", name);
        if(!Schedule_Srv_SelectByName(name)) {
            printf("can not found\n");
        }
        printf("dou you want to query again?(input c to exit, others are yes):");
        scanf("%c", &flag);
        getchar();
        if(flag == 'c') {
            break;
        }
    }while(1);
    return 1;
}