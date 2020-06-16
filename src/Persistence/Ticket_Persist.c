#include "Ticket_Persist.h"
#include "EntityKey_Persist.h"
#include "Play_Persist.h"

#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "../Service/Schedule.h"

#include <stdio.h>
#include <assert.h>

static const char TICKET_DATA_FILE[] = "Ticket.dat";
static const char TICKET_DATE_TEMP_FILE[] = "TicketTmp.dat";
static const char TICKET_KEY_NAME[] = "Ticket";


//标识符：TTMS_SCU_Ticket_Perst_Insert
//功能：存储演出票
int Ticket_Perst_Insert(int schedule_id,seat_list_t list)
{
    FILE *fp = fopen("Ticket.dat","ab");
	
	int rtn = 0;
	seat_list_t temp;
	seat_list_t pos;
	schedule_t sch;
	int sum = 0;

	ticket_t data;

	if(NULL == fp)
	{
		printf( "the file not exist!\n");
		return 0;
	}
	play_t buf;
	Schedule_Perst_SelectByID(schedule_id,&sch);

	Play_Perst_SelectByID(sch.play_id,&buf);
	
	int key = EntKey_Perst_GetNewKeys(TICKET_KEY_NAME,1);
	temp = list;
	pos = list->next;
	while(pos != temp)
	{
		sum++;
		data.id = EntKey_Perst_GetNewKeys(TICKET_KEY_NAME,1);
		data.schedule_id = schedule_id;
		data.seat_id = pos->data.id;
		data.price = buf.price;
		data.status = 0;
	    pos = pos->next;
		rtn = fwrite(&data,sizeof(ticket_t),1,fp);
	}

	fclose(fp);
	return rtn;
}


//标识符:TTMS_SCU_Ticket_Perst_Rem
//功能：根据演出计划ID去除演出票
int Ticket_Perst_Rem(int schedule_id)
{
    int found = -1;
    FILE * fp, *ftp;
    ticket_t buf;
    if (rename("Ticket.dat","TicketTmp.dat") < 0)
    {
        printf("改名失败！");
        return found;
    }
    else
    {
        fp = fopen("TicketTmp.dat","rb");
        ftp = fopen("Ticket.dat","wb+");
        if ( fp == NULL && ftp == NULL)
        {
            printf("文件打开失败");
            return found;
        }
        else
        {
            found = 0;
            while(!feof(fp))
            {
                fread(&buf,sizeof(ticket_t),1,fp);
                if(buf.schedule_id == schedule_id)
                {
                    found++;
                }
                else
                {
                    fwrite(&buf,sizeof(ticket_t),1,ftp);
                }
            }
        }
    }
    fclose(fp);
    fclose(ftp);
    return found;
}


//标识符：TTMS_SCU_Ticket_Perst_SelByID
//功能：根据ID载入演出票
int Ticket_Perst_SelByID(int id, ticket_t *buf)
{
    ticket_t data;
    int found = 0;
    FILE *fp; 
    fp = fopen("Ticket.dat","rb");
    if(fp == NULL)
    {
        printf("Ticket.dat can not be open");
        return found;
    }
    else
    {
        while(!feof(fp))
        {
            fread(&data, sizeof(ticket_t),1,fp);
            if(data.id == id)
            {
                * buf = data;
                found = 1;
                break;
            }
        }
    }
    fclose(fp);
    return found;
}

int Ticket_Perst_Update(ticket_t *buf) {
    assert(NULL!=buf);

    FILE *fp = fopen(TICKET_DATA_FILE, "rb+");
    if (NULL == fp) {
        printf("Cannot open file %s!\n", TICKET_DATA_FILE);
        return 0;
    }

    play_t data;
    int found = 0;

    while (!feof(fp)) {
        if (fread(&data, sizeof(ticket_t), 1, fp)) {
            if (data.id == buf->id) {
                fseek(fp, -((int)sizeof(ticket_t)), SEEK_CUR);
                fwrite(buf, sizeof(ticket_t), 1, fp);
                found = 1;
                break;
            }

        }
    }
    fclose(fp);

    return found;
}

int Ticket_Perst_SelBySeatID(int seat_id, ticket_t *buf) {
    ticket_t data;
    int found = 0;
    FILE *fp;
    fp = fopen("Ticket.dat","rb");
    if(fp == NULL)
    {
        printf("Ticket.dat can not be open");
        return found;
    }
    else
    {
        while(!feof(fp))
        {
            fread(&data, sizeof(ticket_t),1,fp);
            if(data.seat_id == seat_id)
            {
                * buf = data;
                found = 1;
                break;
            }
        }
    }
    fclose(fp);
    return found;
}

