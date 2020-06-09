#include "Play_Persist.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Common/common.h"
#include "../Common/List.h"


/* 获取剧目 */
int Play_Perst_FetchAll(play_list_t list) {
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
    fclose(Play);
    return recCount;
}


/* 存储新剧目 */
int Play_Perst_Insert(play_t *data) {
    int rtn = 0;
    FILE *play;
    play = fopen("../Play.dat", "ab");
    if(play == NULL) {
        printf("error!文件打开失败了\n");
        fclose(play);
        return rtn;
    }
    rtn = fwrite(data, sizeof(play_node_t), 1, play);
    fclose(play);
    return rtn;
}