
#include "Sale_Persist.h"
#include "../Common/list.h"
#include "../Service/Sale.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static const char SALE_DATA_FILE[] = "Sale.dat";
static const char SALE_DATA_TEMP_FILE[] = "SaleTmp.dat";
/*将订单信息插入到文件中*/
int Sale_Perst_Insert(const sale_t *data) {
	assert(NULL!=data);
	FILE *fp=fopen(SALE_DATA_FILE,"ab");
	int rtn=0;
	if (NULL==fp)
	{
		printf("无法打开文件 %s!\n", SALE_DATA_FILE);
		return 0;
	}
	rtn=fwrite(data,sizeof(sale_t),1,fp);
	fclose(fp);
	return rtn;
}

/*将订单信息删除*/
int Sale_Perst_DeleteByID(int saleID) {
	char cmd[100];
	sprintf(cmd, "重命名  %s %s", SALE_DATA_FILE, SALE_DATA_TEMP_FILE);
	system(cmd);

	if(rename(SALE_DATA_FILE, SALE_DATA_TEMP_FILE)<0)
	{
		printf("无法打开文件 %s!\n", SALE_DATA_FILE);
		return 0;
	}
	FILE *fpSour, *fpTarg;
	fpSour = fopen(SALE_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour )
	{
		printf("无法打开文件 %s!\n", SALE_DATA_FILE);
		return 0;
	}
	fpTarg = fopen(SALE_DATA_FILE, "wb");
	if ( NULL == fpTarg )
	{
		printf("无法打开文件 %s!\n", SALE_DATA_TEMP_FILE);
		return 0;
	}

	sale_t buf;
	int found = 0;
	while (!feof(fpSour))
	{
		if (fread(&buf,sizeof(sale_t),1,fpSour))
		{
			if (saleID==buf.id)
			{
				found=1;
				continue;
			}
			fwrite(&buf,sizeof(sale_t),1,fpTarg);
		}
	}
	fclose(fpTarg);
	fclose(fpSour);

	//删除临时文件
	remove(SALE_DATA_TEMP_FILE);

	return found;
}

//根据计划ID载入
int Sale_Perst_SelBySchID(sale_list_t list, int PlayID, user_date_t stDate,
		user_date_t endDate) {
	sale_node_t *p=list->next;
	int found = 0;
	while (p != NULL)
	{
		if(p->data.user_id==usrID && stDate.year<=p->data.date.year && stDate.month<=p->data.date.month && stDate.day<=p->data.date.day && endDate.year>=p->data.date.year && endDate.month>=p->data.date.month && endDate.day>=p->data.date.day )
		{
			found=1;
			break;
		}
		p=p->next;
	}
	return found;
}