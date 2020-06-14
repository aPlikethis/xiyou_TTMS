#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "SalesAnalysis.h"
#include "../Persistence/Sale_Persist.h"
#include "../Persistence/SalesAnalysis_Persist.h"
#include "../Persistence/Ticket_Persist.h"
#include "Sale.h"
#include "Ticket.h"
#include "Play.h"
#include "Schedule.h"
#include "../Common/list.h"

//获取剧目票房
int SalesAnalysis_Srv_StaticSale(salesanalysis_list_t list)
{
    assert(list != NULL);
	play_list_t playList;
	play_node_t *pos;
	salesanalysis_node_t *newNode;
	int sold = 0;
	
	List_Free(list,salesanalysis_node_t);
	List_Init(playList,play_node_t);
	Play_Srv_FetchAll(playList);

	List_ForEach(playList,pos)
	{
		sold++;
		newNode = (salesanalysis_node_t *)malloc(sizeof(salesanalysis_node_t));
		newNode->data.end_date = pos->data.end_date;
		newNode->data.start_date = pos->data.start_date;
		strcpy(newNode->data.area,pos->data.area);
		newNode->data.play_id = pos->data.id;
		newNode->data.price = pos->data.price;
		newNode->data.duration = pos->data.duration;
		strcpy(newNode->data.name,pos->data.name);
		newNode->data.sales = Schedule_Srv_StatRevByPlay(pos->data.id,&newNode->data.totaltickets);
		
		List_AddTail(list,newNode);	
	}

	List_Destroy(playList,play_node_t);
	return sold;
}

//根据剧目ID获取票房
int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount)
{
    int value=0;//保存剧目ID的票房
	int sold=0;//保存剧目ID的有效售票数量
	schedule_list_t list;
	schedule_node_t *p;
	int *soldCount = 0;
	List_Init(list,schedule_node_t);
	Schedule_Srv_SelectByPlayID(list,play_id);
	List_ForEach(list,p){
		value += Ticket_Srv_StatRevBySchID(p->data.id,&sold);
		*soldCount += sold;
	}
	List_Destroy(list,schedule_node_t);
	return value;
}

//根据演出计划ID获取票房
int Ticket_Srv_StatRevBySchID(int schedule_id, int *soldCount)
{
    int value = 0;
	ticket_list_t list;
	ticket_node_t *p;
	*soldCount = 0;
	List_Init(list,ticket_node_t);    
	*soldCount = Ticket_Srv_FetchBySchID(list,schedule_id);
	List_ForEach(list,p){
		sale_node_t *sale = (sale_node_t * )malloc(sizeof(sale_node_t));
		int xxx = Sale_Srv_FetchByTicketID(p->data.id,sale);
		if(p->data.status == 1&&sale->data.type == 1){
			value += p->data.price;
		}
	}
	List_Destroy(list,ticket_node_t);
	return value;
}

//根据演出计划ID获取票的数据
int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id)
{
    int Count = 0;//存放list链表的结点数
	List_Free(list,ticket_node_t);
	Count = Ticket_Perst_SelectBySchID(schedule_id,list);
	if(Count<=0)
	{
		return 0;
	}
	else
	{
		return Count;
	}
}

//对电影票房排序
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list)
{
    assert(list!=NULL);

	salesanalysis_list_t temp=NULL;
	salesanalysis_list_t buf=list->next;
	salesanalysis_list_t flag;
	List_Init(temp,salesanalysis_node_t);
	while(buf!=list)
	{
		if(temp->next == temp)
		{
			List_AddHead(temp,buf);
			flag=temp->next;
		}
		else
		{
			while(flag->data.sales > buf->data.sales)
			{
				flag=flag->next;
			}
			List_InsertBefore(flag,buf);
		}
		buf=list->next;
	}
	list->next = temp->next;
	temp->next->prev = list;
}

//获取全部剧目
int Play_Srv_FetchAll(play_list_t list)
{
    return Play_Perst_FetchAll(list);
}

//根据票ID获取销售记录
int Sale_Srv_FetchByTicketID(int ticket_id, sale_t *sale)
{
    return Sale_Perst_SelByTicketID(ticket_id,sale);
}