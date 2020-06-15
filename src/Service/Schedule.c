#include <stdio.h>
#include "Schedule.h"
#include "../Persistence/Schedule_Persist.h"

int Schedule_Srv_SelectByPlayID(int id, schedule_list_t list) {
    return Schedule_Perst_SelectByPlayID(id, list);
}

int Schedule_Srv_Add(schedule_t *data) {
    return Schedule_Perst_Add(data);
}

int Schedule_Srv_Delete(int id) {
    return Schedule_Perst_DeleteByID(id);
}
int Schedule_Srv_Mod(schedule_t *buf) {
    return Schedule_Perst_Update(buf);
}
int Schedule_Srv_SelectByID(int id, schedule_t *data) {
    return Schedule_Perst_SelectByID(id, data);
}

int Schedule_Srv_SelectByName(char name[]) {
    return Schedule_Perst_SelectByName(name);
}