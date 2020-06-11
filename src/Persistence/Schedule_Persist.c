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