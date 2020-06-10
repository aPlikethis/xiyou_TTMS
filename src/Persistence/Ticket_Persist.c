#include "Ticket_Persist.h"
#include "EntityKey_Persist.h"
#include "Play_Persist.h"
#include "../Service/Ticket.h"
#include "../Service/seat.h"
#include <stdio.h>
#include <assert.h>


//标识符：TTMS_SCU_Schedule_Perst_SelectByID
//功能：根据ID载入演出计划
int Schedule_Perst_SelectByID(int id,schedule_t*buf)
{
    int found = 0;
    FILE *fp; 
    fp = fopen("Schedule.dat","rb");
    if(fp == NULL)
    {
        printf("Schedule.dat can not be open");
        return found;
    }
    else
    {
        while(!feof(fp))
        {
            fread(&date, sizeof(schedule_t),1,fp);
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


//标识符：TTMS_SCU_Ticket_Perst_Insert
//功能：存储演出票
int Ticket_Perst_Insert(int schedule_id,seat_list_t list)
{
    int count,rtn=0;
    schedule_t *sch;
    play_t *buf;
    FILE *fp;
    fp = fopen("Ticket.dat","ab+");

    if(NULL == fp)
    {
        printf("Ticket.dat can not be open");
        return rtn;
    }
    
    else
    {
        sch = (schedule_t *)malloc(sizeof(schedule_t));
        buf = (play_t *)malloc(sizeof(play_t));
    
        Schedule_Perst_SelectByID(schedule_id, sch);
        Play_Perst_SelectByID(sch->play_id, buf);
        count = Seat_Perst_SelectByRoomID(list, sch->id);

        while(count--)
        {
            buf->id =EntKey_Perst_GetNewKeys(buf->name,1);
        }

        seat_node_t *pos;
        pos = list->next;
        while(pos != list)
        {   
            ticket_t.id=buf->id;
            ticket_t.schedule_id=sch.id;
            ticket_t.seat_id=pos->id;
            ticket_t.price=buf->price;
            rtn = fwrite(fp, sizeof(ticket_t), 1, fp);
		    pos=pos->next;
        }
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
    if (rename("Ticke.dat","TicketTmp.dat") < 0)
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
                if(buf.id == schedule_id)
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
int Ticket_Perst_SelBYID(int id, ticket_t *buf)
{
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
            fread(&date, sizeof(ticket_t),1,fp);
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
