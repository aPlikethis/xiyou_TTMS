#include <stdio.h>
#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "Schedule_UI.h"
#include "../Persistence/Schedule_Persist.h"
#include "../Persistence/EntityKey_Persist.h"
#include "../Service/Studio.h"
#include "../Service/Play.h"
#include "../Service/Ticket.h"
#include "../View/Ticket_UI.h"
#include "../View/Sale_UI.h"

/* �����ݳ��ƻ����� */
void Schedule_UI_MgtEntry(int play_id) {
    char choice;
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
  //  while (1) {

    system("cls");
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
//        while(list != NULL) {
//            f = list;
//            list = list->next;
//            free(f);
//        }
        printf("---Total Records:%2d-----Page%2d/%2d---\n",
               paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
        printf("                                       \n");
        printf("==============Operation menu===========\n");
        printf("                                   \n");
        printf("[a]Add a new show plan\n");
        printf("[u]Modify performance plan\n");
        printf("[d]Delete show plan\n");
        printf("[n]Next page\n");
        printf("[l]Last page\n");
        printf("[r]drop out\n");
        scanf("%c", &choice);
        getchar();
        if(choice == 'a' || choice == 'A') {
            if(Schedule_UI_Add()) {
                paging.totalRecords = Schedule_Srv_SelectByPlayID(play_id, list);
                printf("Added successfully\n");
            }
            else {
                printf("add failed\n");
            }

        }
        if(choice == 'u' || choice == 'U') {
            if(Schedule_UI_Mod()) {
                printf("Successfully modified\n");
            }
            else {
                printf("failed not to modify\n");
            }
            paging.totalRecords = Schedule_Srv_SelectByPlayID(play_id, list);
        }
        if(choice == 'd' || choice == 'D') {
            if(Schedule_UI_Del()) {
                printf("successfully deleted\n");
            }
            else {
                printf("can not to delete\n");
            }
            paging.totalRecords = Schedule_Srv_SelectByPlayID(play_id, list);
        }
        if(choice == 'l' || choice == 'L') {
            if (!Pageing_IsFirstPage(paging)) {
                Paging_Locate_OffsetPage(list, paging, -1, schedule_node_t);
                paging.totalRecords = Schedule_Srv_SelectByPlayID(play_id, list);
            }
        }
        if(choice == 'n' || choice == 'N') {
            if (!Pageing_IsLastPage(paging)) {
                Paging_Locate_OffsetPage(list, paging, 1, schedule_node_t);
                paging.totalRecords = Schedule_Srv_SelectByPlayID(play_id, list);
            }
        }
        if(choice != 'r' && choice != 'R') {
            Schedule_UI_MgtEntry(play_id);
        }


    //}
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
        else if(data.play_id == 0) {
            return 0;
        }
        else {
            printf("Please enter again('0' to return)\n");
        }
    }while(1);
    
    do {                    
        printf("Please enter the studio ID:");
        scanf("%d", &data.studio_id);
         if(Studio_Srv_FetchByID(data.studio_id, &studio_data)) {
             data.seat_count = studio_data.rowsCount * studio_data.colsCount;
             break;
         }
         else if(data.studio_id == 0) {
             return 0;
         }
         else {
             printf("Please enter again('0' to return)\n");
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
    else {
        return 0;
    }
    Ticket_UI_MgtEntry(data.id);
    return rtn;
}

/* ɾ�� */
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
            if(Play_Srv_FetchByID(data.play_id, &play_data)) {
                break;
            }
            else {
                printf("can not found Play! Please enter again\n");
            }
        }while(1);
    
        do {
        printf("Please enter the hall ID:");
        scanf("%d", &data.studio_id);
            if(Studio_Srv_FetchByID(data.studio_id, &studio_data)) {
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
        getchar();
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

void Schedule_UI_Print(int id) {
    char choice;
    Pagination_t paging;
    schedule_list_t list, f;
    schedule_node_t *p;
    int i;

    List_Init(list, schedule_node_t);
    list->next = NULL;
    paging.offset = 0;
    paging.pageSize = 5;
    paging.totalRecords = Schedule_Srv_SelectByPlayID(id, list);
    Paging_Locate_FirstPage(list, paging);
    //  while (1) {


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

    printf("---Total Records:%2d-----Page%2d/%2d---\n",
           paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
    printf("                                       \n");
    printf("==============Operation menu===========\n");
    printf("                                   \n");
    printf("[N]Next page\n");
    printf("[L]Last page\n");
    printf("[S]sale ticket\n");
    printf("[R]drop out\n");
    scanf("%c", &choice);
    getchar();




    if(choice == 'l' || choice == 'L') {
        if (!Pageing_IsFirstPage(paging)) {
            Paging_Locate_OffsetPage(list, paging, -1, schedule_node_t);
            paging.totalRecords = Schedule_Srv_SelectByPlayID(id, list);
        }
    }
    if(choice == 'n' || choice == 'N') {
        if (!Pageing_IsLastPage(paging)) {
            Paging_Locate_OffsetPage(list, paging, 1, schedule_node_t);
            paging.totalRecords = Schedule_Srv_SelectByPlayID(id, list);
        }
    }
    if(choice == 's' || choice == 'S') {
        Sale_UI_MgtEntry();
    }

    if(choice == 'r' || choice == 'R') {
        return;
    }
}