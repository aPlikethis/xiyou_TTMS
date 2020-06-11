#include <stdio.h>
#include "../Service/Schedule.h"
#include "../Common/List.h"

/* 查询所有演出厅 */
int Schedule_Perst_FechAll(int id, schedule_list_t list) {
    FILE *schedule = fopen("../Schedule.dat","rb");
    int recount = 0;
    if(schedule == NULL) {
        printf("文件打开失败\n");
        return recount;
    }
    schedule_list_t node, end = list;
    schedule_t *data;
    

    while(!feof(schedule)) {
        fread(data, sizeof(schedule_t), 1, schedule);
        if(data->play_id == id) {
            node->data = *data;
            List_InsertAfter(end, node);
            end = end->next;
            recount++;
        }
    }
    fclose(schedule);
    return recount;
}


int Schedule_Perst_Add(schedule_t *data) {
    int rtn = 0;
    FILE *schedule = fopen("../Schedule.dat", "wb"); 
    if(schedule == NULL) {
        printf("文件打开失败\n");
        return rtn;
    }
    fwrite(data, sizeof(schedule_t), 1, schedule);
    rtn = 1;
    fclose(schedule);
    return rtn;
}

int Schedule_Perst_Del(int id) {
    int rtn = 0;
    schedule_list_t list;
    List_Init(list, schedule_node_t);
    schedule_node_t *end = list;
    schedule_node_t *node;
    schedule_t data;
    FILE schedule = fopen("../Schedule.dat", "rb+");
    if(schedule == NULL) {
        printf("文件打开失败了\n");
        return rtn;
    }
    while(!feof(schedule)) {
        fread(data, sizeof(schedule_t), 1, schedule);
        if(data.id != id) {
            node->data = data;
            List_InsertAfter(end, node);
            end = end->next;
        }   
    }
    list = list->next;
    while(list != NULL) {
        fwrite(&(list->data), sizeof(schedule_t), 1, schedule);
        list = list->next;
    }
    rtn = 1;
    fclose(schedule);
    return rtn;
}