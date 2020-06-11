#include <stdio.h>
#include "Schedule.h"

int Schedule_Srv_FechAll(int id, schedule_list_t list) {
    return Schedule_Perst_FechAll(id, list);
}