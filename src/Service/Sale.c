#include "../Persistence/Sale_Persist.h"
#include "../Persistence/Query_Persist.h"

//根据票的信息插入到订单的信息
inline int Sale_Srv_Add(const sale_t *data) {
	return Sale_Perst_Insert(data);

//删除订单的信息
inline int Sale_Srv_DeleteByID(int saleID) {
	return Sale_Perst_DeleteByID(saleID);
}

//根据票ID获取销售记录
int Sale_Srv_FetchByTicketID(int ticket_id,sale_t *sale)
{
	sale_t *p=list->next;
	int found = 0;
	while (p != NULL)
	{
		if(p->data.ticket_id==ticket_id && stDate.year<=p->data.date.year && stDate.month<=p->data.date.month && stDate.day<=p->data.date.day && endDate.year>=p->data.date.year && endDate.month>=p->data.date.month && endDate.day>=p->data.date.day )
		{
			found=1;
			break;
		}
		p=p->next;
	}
}
	return Sale_Perst_SelByTicketID(ticket_id,sale);
}