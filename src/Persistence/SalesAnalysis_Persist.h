#ifndef SALESANALYSIS_PERSIST_H_
#define SALESANALYSIS_PERSIST_H_

#include "../Service/Sale.h"
#include "../Service/SalesAnalysis.h"
#include "../Service/Play.h"
#include "../Service/Ticket.h"

int Sale_Perst_SelByTicketID (int ticket_id, sale_t *sale);
//int Ticket_Perst_SelectBySchID(ticket_list_t list, int schedule_id);

#endif