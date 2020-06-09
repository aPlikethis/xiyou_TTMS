#include "Play.h"
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

/* 获取剧目 */
int Play_Srv_FetchAll(play_list_t list) {
    int recCount = 0;
    FILE *Play;
    play_list_t end = list;
    Play = fopen("Play.dat", "rb");
    if(Play == NULL) {
        printf("ERROR!文件不存在");
        fclose(Play);
        return recCount;
    }
    while(feof(Play)) {
        play_list_t node = (play_list_t)malloc(sizeof(play_node_t));
        fread(node, sizeof(play_node_t), 1, Play);
        end->next = node;
        end = end->next;
        recCount++;
    }
    end->next = NULL;
    return recCount;
}