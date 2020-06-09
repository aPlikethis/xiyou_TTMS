#include "Play.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Common/common.h"

play_list_t Play_Srv_FetchByID(play_list_t list, int id) {
    play_list_t node = list->next;
    while(node != NULL) {
        if(node->date.id == id) {
            return node;
        }
    }
}