

#include "../Common/list.h"
#include "Account_Persist.h"
#include "EntityKey_Persist.h"	
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

static const char ACCOUNT_DATA_FILE[] = "Account.dat";
static const char ACCOUNT_DATA_TEMP_FILE[] = "AccountTmp.dat";
static const char ACCOUNT_KEY_NAME[] = "Account";

//�ж��ļ��Ƿ����
int Account_Perst_CheckAccFile()
{
    if(access(ACCOUNT_DATA_FILE,0)==0)  //access(�ļ�����0)�ж��ļ��Ƿ����
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

//ͨ���û�������ϵͳ�û�
int Account_Perst_SelByName(char usrName[], account_t *buf)

{
    assert(NULL!=buf);
    
    FILE *fp;
    fp = fopen(ACCOUNT_DATA_FILE,"rb");
    if(NULL==fp){
    	return 0;
	}
	
	account_t data;
	int found = 0;
	
	while(!feof(fp)){
		if(fread(&data,sizeof(account_t),1,fp)){
			if(!strcmp(usrName,data.username)){
				*buf = data;
				found = 1;
				break;
			}
		}
	}
	fclose(fp);
	
	return found;
}

//ͨ���û�ID����ϵͳ�û�
int Account_Perst_SelectByID(int id, account_t *buf)
{
    assert(buf!=NULL);
    
    FILE*fp;
	fp = fopen(ACCOUNT_DATA_FILE,"rb");
    if(fp==NULL){
    	return 0;
	}
	
	account_t data;
	int found = 0;
	while(!feof(fp)){
		if(fread(&data,sizeof(account_t),1,fp)){
			if(id==data.id){
				*buf = data;
				found = 1;
				break;
			}
		}
	}
	fclose(fp);
	return found;
}

//����ϵͳ�û�
int Account_Perst_Update(account_t *data)
{
    assert(data!=NULL);
    FILE *fp = fopen(ACCOUNT_DATA_FILE,"rb+");
    if(fp==NULL)
    {
        printf("Cannot open file %s!\n",ACCOUNT_DATA_FILE);
        return 0;
    }

    account_t buf;
    int found = 0;
    while (!feof(fp))
    {
        if(fread(&buf,sizeof(account_t),1,fp))
        {
            if(buf.id==data->id)
            {
                fseek(fp,-((int)sizeof(account_t)),SEEK_CUR);
                fwrite(data,sizeof(account_t),1,fp);
                found = 1;
                break;
            }
        }
    }
    fclose(fp);

    return found;
}

//����ϵͳ�û�
int Account_Perst_Insert(account_t *data) {
    assert(NULL!=data);

	long key = EntKey_Perst_GetNewKeys(ACCOUNT_KEY_NAME, 1); //Ϊ���ݳ��������ȡ
	if(key<=0)			//��������ʧ�ܣ�ֱ�ӷ���
		return 0;
	data->id = key;

    FILE *fp = fopen(ACCOUNT_DATA_FILE,"ab");
    int ret = 0;
    if(NULL==fp){
    	printf("Cannot open file %s!\n", ACCOUNT_DATA_FILE);
    	return 0;
	}
	ret = fwrite(data,sizeof(account_t),1,fp);
	
	fclose(fp);
	return ret;
}

//ɾ��ϵͳ�û�
int Account_Perst_RemByID(int id)
{
	//��ԭʼ�����ļ�������
	if(rename(ACCOUNT_DATA_FILE, ACCOUNT_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n", ACCOUNT_DATA_FILE);
		return 0;
	}

    FILE *fp1,*fp2;
    fp1 = fopen(ACCOUNT_DATA_TEMP_FILE,"rb");
    if(fp1 == NULL){
    	printf("Cannot open file %s!\n",ACCOUNT_DATA_FILE);
    	return 0;
	}
    fp2 = fopen(ACCOUNT_DATA_FILE,"wb");
    if(fp2==NULL){
    	printf("Cannot open file %s!\n",ACCOUNT_DATA_FILE);
    	return 0;
	}
	
	account_t buf;
	int found = 0;
	while(!feof(fp1)){
		if(fread(&buf,sizeof(account_t),1,fp1)){
			if(id==buf.id){
				found = 1;
				continue;
			}
			fwrite(&buf,sizeof(account_t),1,fp2);
		}
	}
    
    fclose(fp2);
    fclose(fp1);
	
	//ɾ����ʱ�ļ�
	remove(ACCOUNT_DATA_TEMP_FILE);

    return found;
}

//��ȡ����ϵͳ�û�
int Account_Perst_SelectAll(account_list_t list)
{
    account_node_t *pNew;
    account_t data;
    int retCount = 0;
    
    assert(list!=NULL);
    List_Free(list,account_node_t);
    FILE *fp = fopen(ACCOUNT_DATA_FILE,"rb");
    if(fp==NULL){
    	return 0;
	}
	
	while(!feof(fp)){
		if(fread(&data,sizeof(account_t),1,fp)){
			pNew = (account_node_t*) malloc(sizeof(account_node_t));
			if(!pNew){
				printf("Warning, Memory OverFlow!!!\nCannot Load more Data into memory!!!\n");
				break;
			}
			pNew->data = data;
			List_AddTail(list,pNew);
			retCount++;
		}
	}
	fclose(fp);
	return retCount;
}
