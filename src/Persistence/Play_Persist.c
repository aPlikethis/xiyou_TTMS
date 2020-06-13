#include "Play_Persist.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Common/common.h"
#include "../Common/List.h"
#include "EntityKey_Persist.h"
#include "../Service/Play.h"

static const char PLAY_DATA_FILE[] = "Play.dat"; 
static const char PLAY_DATA_TEMP_FILE[] = "Play.dat"; //��Ŀ��ʱ�ļ������� 
static const char PLAY_KEY_NAME[] = "Play"; //��Ŀ������ 


/* ��ȡ��Ŀ */
int Play_Perst_FetchAll(play_list_t list) {
    int recCount = 0;
    FILE *Play;
    play_list_t end = list;
    play_list_t node = (play_list_t)malloc(sizeof(play_node_t));
    Play = fopen("../Play.dat", "rb");
    if(Play == NULL) {
        printf("ERROR!dirctry failed ");
        return recCount;
    }
    play_t data;
    while(!feof(Play)) {
        fread(&data, sizeof(play_t), 1, Play);
        node->data = data;
        List_InsertAfter(end, node);
        end = end->next;
        recCount++;
    }
    end->next = NULL;
    fclose(Play);
    return recCount;
}


/* �洢�¾�Ŀ */
int Play_Perst_Insert(play_t *data) {
    long key = EntKey_Perst_GetNewKeys(PLAY_KEY_NAME, 1); //Ϊ�¾�Ŀ�����ȡ
	if(key<=0) {
		return 0;
    }			//��������ʧ�ܣ�ֱ�ӷ���

	data->id = key;
    int rtn = 0;
    FILE *play;
    play = fopen("../Play.dat", "ab");
    if(play == NULL) {
        printf("error!�ļ���ʧ����\n");
        return rtn;
    }
    fwrite(data, sizeof(play_node_t), 1, play);
    rtn = 1;
    fclose(play);
    return rtn;
}

/* ����id��ѯ��Ŀ��Ϣ */
int Play_Perst_SelectByID(int id, play_t *buf) {
    int found = 0;
    FILE *play = fopen("../play.dat", "rb");
    if(play == NULL) {
        printf("play.dat�ļ���ʧ��\n");
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

/* ���¾�Ŀ */
int Play_Perst_Update(const play_t *data) {
    int found = 0;
    play_t *buf;
    FILE *play = fopen("../Play.dat", "rb+");
    if(play == NULL) {
        printf("Play.dat�ļ���ʧ��\n");
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
/* ɾ����Ŀ */
int Play_Perst_Delete(int id, play_list_t list) {
    play_list_t node = list;
    int rtn = 0;
    FILE *play;
    play = fopen("../Play.dat", "wb");
    if(play == NULL) {
        printf("ERROR!�ļ�������");
        fclose(play);
        return rtn;
    }
    while(node->data.id != id) {
        node = node->next;
        if(node == NULL) {
            fclose(play);
            return rtn;
        }
    }
    rtn = 1;
    List_FreeNode(node);
    while(list != NULL) {
        fwrite(&(list->data), sizeof(play_t), 1, play);
    }
    
    fclose(play);
    return rtn;
}