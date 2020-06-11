#include <stdio.h>
#include "Schedule.h"
#include "../Persistence/Schedule_Persist.h"

int Schedule_Srv_FechAll(int id, schedule_list_t list) {
    return Schedule_Perst_FechAll(id, list);
}

int Schedule_Srv_Add(schedule_t *data) {
    return Schedule_Perst_Add(data);
}

int Schedule_Srv_Del(int id) {
    return Schedule_Perst_Del(id);
}
int Schedule_Srv_Mod(schedule_t *buf) {
    return Schedule_Perst_Update(buf);
}
int Schedule_Srv_SelectByID(int id, schedule_t *data) {
    return Schedule_Srv_SelectByID(id, data);
}