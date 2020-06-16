#ifndef SLAEINGPERSIST_H
#define SLAEINGPERSIST_H

#include "../Service/Sale.h"
#include "../Common/common.h"

int Sale_Perst_Insert(const sale_t *data);
int Sale_Perst_Update(int saleID);
int Sale_Perst_SelByID(sale_list_t list,int usrID);
int Ticket_Perst_SelectBySchID(int id, ticket_list_t list);
int Sale_Perst_selByUserId(int user_id, sale_list_t list);

#endif