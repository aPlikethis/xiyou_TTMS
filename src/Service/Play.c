#include "Play.h"
#include "../Persistence/Play_Persist.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Common/common.h"

/* 查询剧目，返回该剧目的节点指针 */
play_list_t Play_Srv_FetchByID(play_list_t list, int id) {
    play_list_t node = list->next;
    while(node != NULL) {
        if(node->date.id == id) {
            return node;
        }
        node = node->next;
    }
}

/* 获取全部剧目 */
int Play_Srv_FetchAll(play_list_t list) {
    return Play_Perst_FetchAll(list);
}

int Play_Srv_Add(play_t *data) {
    return Play_Perst_Insert(data);
}