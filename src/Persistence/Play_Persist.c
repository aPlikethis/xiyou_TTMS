#include "Play_Persist.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Common/common.h"
#include "../Common/List.h"
#include "EntityKey_Persist.h"
#include "../Service/Play.h"

static const char PLAY_DATA_FILE[] = "Play.dat"; 
static const char PLAY_DATA_TEMP_FILE[] = "Playtem.dat"; //剧目临时文件名常量 
static const char PLAY_KEY_NAME[] = "Play"; //剧目名常量 


/* 获取剧目 */
int Play_Perst_FetchAll(play_list_t list) {
    int recCount = 0;
    FILE *Play;
    play_list_t end = list;
    Play = fopen("Play.dat", "rb");
    if(Play == NULL) {
        printf("Play.dat file not found, have not play.\n");
        return recCount;
    }
    play_t data;
    while(fread(&data, sizeof(play_t), 1, Play)) {
      /*   fread(data, sizeof(play_t), 1, Play); */
        
        play_list_t node = (play_list_t)malloc(sizeof(play_node_t));
        node->data = data;
        end->next = node;
        node->prev = end;
        node->next = NULL;
        end = end->next;
        recCount++;
    }
    fclose(Play);
    return recCount;
}


/* 存储新剧目 */
int Play_Perst_Insert(play_t *data) {	 
	assert(NULL!=data);

	long key = EntKey_Perst_GetNewKeys(PLAY_KEY_NAME, 1);
	if(key<=0)			//主键分配失败，直接返回
		return 0;
	data->id = key;		//赋给新对象带回到UI层
	FILE *fp = fopen(PLAY_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n", PLAY_DATA_FILE);
		return 0;
	}

	rtn = fwrite(data, sizeof(play_t), 1, fp);

	fclose(fp);
	return rtn;
}

/* 根据id查询剧目信息 */
int Play_Perst_SelectByID(int id, play_t *buf) {
    int found = 0;
    FILE *play = fopen("play.dat", "rb");
    if(play == NULL) {
        printf("play.dat文件打开失败\n");
        return found;
    }
    play_t data;
    while(fread(&data, sizeof(play_t), 1, play)) {
        if(data.id == id) {
            *buf = data;
            found = 1;
            fclose(play);
            return found;
        }
    }
}

/* 更新剧目 */
int Play_Perst_Update(const play_t * data) {
	assert(NULL!=data);

	FILE *fp = fopen(PLAY_DATA_FILE, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", PLAY_DATA_FILE);
		return 0;
	}

	play_t buf;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&buf, sizeof(play_t), 1, fp)) {
			if (buf.id == data->id) {
				fseek(fp, -((int)sizeof(play_t)), SEEK_CUR);
				fwrite(data, sizeof(play_t), 1, fp);
				found = 1;
				break;
			}

		}
	}
	fclose(fp);

	return found;
}

/* 删除剧目 */
int Play_Perst_DeleteByID(int id) {

	//将原始文件重命名，然后读取数据重新写入到数据文件中，并将要删除的实体过滤掉。

	//对原始数据文件重命名
	if(rename(PLAY_DATA_FILE, PLAY_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n", PLAY_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(PLAY_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour ){
		printf("Cannot open file %s!\n", PLAY_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(PLAY_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("Cannot open file %s!\n", PLAY_DATA_TEMP_FILE);
		return 0;
	}


	play_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(play_t), 1, fpSour)) {
			if (id == buf.id) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(play_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//删除临时文件
	remove(PLAY_DATA_TEMP_FILE);
	return found;
}