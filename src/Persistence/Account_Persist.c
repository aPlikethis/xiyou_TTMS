

#include "Account_Persist.h"
#include "../Service/Account.h"
#include "../Common/list.h"
#include "EntityKey_Persist.h"	
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>
#include <string.h>

static const char ACCOUNT_DATA_FILE[] = "Account.dat";
static const char ACCOUNT_DATA_TEMP_FILE[] = "AccountTmp.dat";
static const char ACCOUNT_KEY_NAME[] = "Account";

//判断账号文件是否存在.存在返回1，不存在返回0
int Account_Perst_CheckAccfile()
{
    if(access(ACCOUNT_DATA_FILE,0)==0)  //access(文件名，0)判断文件是否存在
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}
//更新系统用户
int Account_Perst_Update(const account_t *data)
{
    assert(date!=NULL);
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

//根据用户名载入账号,载入成功 return 1；否则 return 0
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
int Account_Perst_Insert(account_t *data) {
    assert(NULL!=data);

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

int Account_Perst_DeleteByID(int id)
{
    FILE *fp1,*fp2;
    fp1 = fopen(ACCOUNT_DATA_TEMP_FILE,"rb");
    if(fp1 == NULL){
    	printf("Cannot open file %s!\n",ACCOUNT_DATA_FILE);
    	RETURN 0;
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
    return found;
}

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

int Account_Perst_SelectAll(account_list_t list)
{
    account_node_t *pNew;
    account_t data;
    int retCount = 0;
    
    assert(lst!=NULL);
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