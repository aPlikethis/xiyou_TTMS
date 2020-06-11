#include <stdio.h>
#include "Schedule.h"
#include "../Persistence/Schedule_Persist.h"

int Schedule_Srv_FechAll(int id, schedule_list_t list) {
    return Schedule_Perst_FechAll(id, list);
}

int Schedule_Srv_Add(schedule_t *data) {
    return Schedule_Perst_Add(data);
}