#ifndef 	SALETICKET_UI_H_
#define 	SALETICKET_UI_H_

#include "../Service/play.h"
#include "../Service/schedule.h"
#include "../Service/seat.h"
#include "../Service/account.h"
#include "../Service/Ticket.h"


//售票主菜单
void Sale_UI_MgtEntry();

//根据剧目ID显示演出计划
void Sale_UI_ShowScheduler(int playID);


//根据演出计划ID，显示演出票
void Sale_UI_ShowTicket(int schID);

//售票
int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList, int studioID);

//退票
void Sale_UI_ReturnTicket();

#endif
