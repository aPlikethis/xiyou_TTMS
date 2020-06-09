#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../Common/list.h"
#include "../Service/SalesAnalysis.h"
#include "../Service/Sale.h"
#include "../Persistence/EntityKey_Persist.h"

static const char SALESANALYSIS_DATA_FILE[] = "salesanalysis.dat";

//将一条salesanalysis记录写入salesanalysis.dat文件;成功返回1，失败返回0
int Salesanalysis_Perst_Insert(const salesanalysis_t *data)
{
    assert(data!=NULL);//assert相当于if else，且仅在debug版本下起作用
    FILE *fp=fopen(SALESANALYSIS_DATA_FILE,"ab");
    int rtn=0;
    if(fp=NULL)
    {
        printf("无法打开文件 %s!\n", SALESANALYSIS_DATA_FILE);
		return 0;
    }
    rtn=fwrite(data,sizeof(salesanalysis_t),1,fp);//fwrite返回成功写入项的数量
	fclose(fp);
	return rtn;
}

//遍历读salesanalysis.dat文件建立salesanalysis链表
int SalesAnalysis_Perst_SelectAll(salesanalysis_list_t list)
{
    salesanalysis_node_t *newNode;
    salesanalysis_t data;
    int recCount=0;
}

//遍历读Sale.dat文件建立list 链表，返回链表list长度
int Sale_Perst_SelectAll(sale_list_t list)
{
    sale_node_t *newNode;
    sale_t data;
    int recCount = 0;
}