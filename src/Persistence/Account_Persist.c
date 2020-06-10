

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