#include "Play_Persist.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Common/common.h"
#include "../Common/List.h"
#include "EntityKey_Persist.h"


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
    play_t *data = (play_t *)malloc(sizeof(play_t));
    while(feof(Play)) {
        fread(data, sizeof(play_t), 1, Play);
        play_list_t node = (play_list_t)malloc(sizeof(play_node_t));
        node->date = *data;
        node->next = NULL;
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
    EntKey_Perst_GetNewKeys(data, 1);
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

/* 根据id查询剧目信息 */
int Play_Perst_SelectByID(int id, play_t *buf) {
    int found = 0;
    FILE *play = fopen("../play.dat", "rb");
    if(play == NULL) {
        printf("play.dat文件打开失败\n");
        return found;
    }
    play_t data;
    while(1) {
        fread(&data, sizeof(play_t), 1, play);
        if(data.id == id) {
            buf = &data;
            found = 1;
            fclose(play);
            return found;
        }
    }
}

/* 更新剧目 */
int Play_Perst_Update(const play_t *data) {
    int found = 0;
    play_t *buf;
    FILE *play = fopen("../Play.dat", "rb+");
    if(play == NULL) {
        printf("Play.dat文件打开失败\n");
        return found;
    }
    while(!feof(play)) {
        if (fread(&buf, sizeof(play_t), 1, play)) {
			if (buf->id == data->id) {
				fseek(play, -((int)sizeof(play_t)), SEEK_CUR);
				fwrite(data, sizeof(play_t), 1, play);
				found = 1;
				break;
			}
		}
    }
    fclose(play);

	return found;
}