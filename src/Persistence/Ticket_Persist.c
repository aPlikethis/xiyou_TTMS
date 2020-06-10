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
    ticket_node_t *ticketdata;
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
        
        seat_node_t *pos;
        pos = list->next;
        while(pos != list)
        {   
            ticketdata = (seat_list_t)malloc((int)sizeof(seat_node_t));
            ticketdate->date.id =EntKey_Perst_GetNewKeys(buf->name,1);
            ticketdate->date.schedule_id=sch.id;
            ticketdate->date.seat_id=pos->id;
            ticketdate->date.price=buf->price;
            ticketdate->date.status=TICKET_AVL
            rtn = fwrite(&（ticketdate->date）, sizeof(ticket_t), 1, fp);
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

}

//查询所有票信息
int Ticket_Perst_FetchAll(ticket_list_t list)
 {
    int recCount = 0;
    FILE *Ticket;
    ticket_list_t end = list;
    Ticket = fopen("ticket.dat", "rb");
    if(Ticket == NULL) {
        printf("ERROR!文件不存在");
        fclose(Ticket);
        return recCount;
    }
    ticket_t *data = (ticket_t *)malloc(sizeof(ticket_t));
    while(feof(Ticket)) {
        fread(data, sizeof(ticket_t), 1, Ticket);
        ticket_list_t node = (ticket_list_t)malloc(sizeof(ticket_node_t));
        List_InsertAfter(end, node);
        end = node;
        recCount++;
    }
    fclose(Ticket);
    return recCount;
}
