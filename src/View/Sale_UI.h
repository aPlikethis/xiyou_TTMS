#ifndef 	SALETICKET_UI_H_
#define 	SALETICKET_UI_H_

#include "../Service/play.h"
#include "../Service/schedule.h"
#include "../Service/seat.h"
#include "../Service/account.h"
#include "../Service/Ticket.h"
static const int TICKET_PAGE_SIZE = 5;
static const int SCHEDULE_PAGE_SIZE = 5;
static const int PLAY_PAGE_SIZE = 5;


int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList);


void Sale_UI_MgtEntry();

//退票
void Sale_UI_ReturnTicket();


#endif
