#include <stdio.h>
#include <stdlib.h>
#include "../Service/Schedule.h"
#include "../Common/List.h"
#include "../Persistence/EntityKey_Persist.h"
#include "../Service/Play.h"
#include "Schedule_Persist.h"
#include "../Common/common.h"
#include "../View/Schedule_UI.h"
#include "../View/Sale_UI.h"


static const char SCHEDULE_DATA_FILE[] = "Schedule.dat"; 
static const char SCHEDULE_DATA_TEMP_FILE[] = "Scheduletem.dat"; 
static const char SCHEDULE_KEY_NAME[] = "Schedule"; 
/* 查询所有演出厅 */
int Schedule_Perst_SelectByPlayID(int id, schedule_list_t list) {
    FILE *schedule = fopen("Schedule.dat","rb");
    int recount = 0;
    if(schedule == NULL) {
        printf("can not open file\n");
        return recount;
    }
    schedule_list_t end = list;
    schedule_t data;
    

    while(!feof(schedule)) {
        if(fread(&data, sizeof(schedule_t), 1, schedule)) {
            if (data.play_id == id) {
                schedule_list_t node = (schedule_list_t) malloc(sizeof(schedule_node_t));
                node->data = data;
                end->next = node;
                node->prev = end;
                node->next = NULL;
                end = end->next;
                recount++;
            }
        }
    }
    fclose(schedule);
    return recount;
}


int Schedule_Perst_Add(schedule_t *data) {
    assert(NULL!=data);

	long key = EntKey_Perst_GetNewKeys(SCHEDULE_KEY_NAME, 1);
	if(key<=0)			//主键分配失败，直接返回
		return 0;
	data->id = key;		//赋给新对象带回到UI层
    int rtn = 0;
    FILE *schedule = fopen("Schedule.dat", "ab"); 
    if(schedule == NULL) {
        printf("can not open file\n");
        return rtn;
    }
    rtn = fwrite(data, sizeof(schedule_t), 1, schedule);
    fclose(schedule);
    return rtn;
}

int Schedule_Perst_DeleteByID(int id) {

	//将原始文件重命名，然后读取数据重新写入到数据文件中，并将要删除的实体过滤掉。

	//对原始数据文件重命名
	if(rename("Schedule.dat", "Scheduletem.dat")<0){
		printf("error1:Cannot open file %s!\n", SCHEDULE_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(SCHEDULE_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour ){
		printf("error2:Cannot open file %s!\n", SCHEDULE_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(SCHEDULE_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("error3:Cannot open file %s!\n", SCHEDULE_DATA_TEMP_FILE);
		return 0;
	}


	schedule_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(schedule_t), 1, fpSour)) {
			if (id == buf.id) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(schedule_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//删除临时文件
	remove(SCHEDULE_DATA_TEMP_FILE);
	return found;
}




int Schedule_Perst_Update(schedule_t *data) {
	assert(NULL!=data);

	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
		return 0;
	}

	schedule_t buf;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&buf, sizeof(schedule_t), 1, fp)) {
			if (buf.id == data->id) {
				fseek(fp, -((int)sizeof(schedule_t)), SEEK_CUR);
				fwrite(data, sizeof(schedule_t), 1, fp);
				found = 1;
				break;
			}

		}
	}
	fclose(fp);

	return found;
}

int Schedule_Perst_SelectByID(int id, schedule_t *data) {
    int rtn = 0;
    FILE *sch = fopen("Schedule.dat", "rb");
    if(sch == NULL) {
        printf("can not open file Schedule.dat\n");
        return rtn;
    }
    while(!feof(sch)) {
        fread(data, sizeof(schedule_t), 1, sch);
        if(data->id == id) {
            rtn = 1;
            return rtn;
        }
    }
    return rtn;
}

int Schedule_Perst_SelectByName(char name[]) {
    int found = 0;
	int flag;
    FILE *play, *sch;
    play_t play_data;
    play = fopen("play.dat","rb");
    do {
        fread(&play_data, sizeof(play_t), 1, play);
		flag = StrCmp(name, play_data.name);
    }
    while(!flag && !feof(play));
	if(flag == 0) {
		return found;
	}
	else {
		Schedule_UI_Print(play_data.id);
		found = 1;
		return found;
	}

    
    return found;
}