#include "Sale_Persist.h"
#include "../Common/List.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Service/Ticket.h"
int Sale_Perst_Insert(const sale_t *data){
    FILE *fp;
    int rtn;
    fp = fopen("Sale.dat", "ab");
    if (fp == NULL) {
        printf("can't open Sale.dat");
    } else {
        rtn = fwrite(&data, sizeof(sale_t), 1, fp);
    }
    fclose(fp);
    return rtn;
}

int Sale_Perst_DeleteByID(int saleID);

int Ticket_Perst_Update(const ticket_t *data){
	assert(NULL!=data);

	FILE *fp = fopen("Ticket.dat", "rb+");
	if (NULL == fp)
	{
		printf("无法打开文件 %s!\n", "Ticket.dat");
		return 0;
	}

	ticket_t buf;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&buf, sizeof(ticket_t), 1, fp))
		{
			if (buf.id == data->id)
			{
				fseek(fp, -sizeof(ticket_t), SEEK_CUR);
				fwrite(data, sizeof(ticket_t), 1, fp);
				found = 1;
				break;
			}

		}
	}
	fclose(fp);

	return found;
}
//根据用户ID载入给定时间区间内的销售记录
int Sale_Perst_SelectByUsrID(sale_list_t list, int usrID,
		user_date_t stDate, user_date_t endDate);

//根据用户ID载入给定时间区间内的销售记录
int Sale_Perst_SelectByDate(sale_list_t list,
		user_date_t stDate, user_date_t endDate);

int Ticket_Srv_SelBySchID(int id, ticket_t *buf) {
      //  List_Init(list, ticket_node_t);
        FILE *fp;
        ticket_t data;
        fp = fopen("Ticket.dat", "rb");
        if (fp == NULL) {
            printf("Ticket.dat can not be open !");
        } else {
            while (!feof(fp)) {
                fread(&data, sizeof(ticket_t), 1, fp);
                if (data.id == id) {
                    *buf = data;
                    return 1;
                }
            }
        }
        fclose(fp);
        return 0;
}

int Ticket_Perst_SelectAll(ticket_list_t list,int schID)
{
    ticket_node_t *newNode;
	ticket_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, ticket_node_t);

	FILE *fp = fopen("Ticket.dat", "rb+");
	if (NULL == fp) { //文件不存在
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(ticket_t), 1, fp)) {
            if(data.schedule_id == schID)
            {
                newNode = (ticket_node_t*) malloc(sizeof(ticket_node_t));
                if (!newNode) {
                    printf("Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
                    break;
                }
                newNode->data = data;
                List_AddTail(list, newNode);
                recCount++;
            }

		}
	}
	fclose(fp);
	return recCount;

}

int Sale_Perst_SelByTicketID (int ticket_id, sale_t *sale) {
    assert(NULL != sale);
    FILE *fp = fopen("Sale.dat", "rb");
    if (NULL == fp) {
        return 0;
    }
    sale_t data;
    int found = 0;
    while (!feof(fp))
    {
        if (fread(&data, sizeof(sale_t), 1, fp))
        {
            if (ticket_id == data.ticket_id)
            {
                *sale =  data;
                found = 1;
                break;
            };
        }
    }
    fclose(fp);
    return found;
}

