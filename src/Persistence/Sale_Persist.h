#ifndef SLAEINGPERSIST_H
#define SALEINGPERSIST_H

#include "../Service/Sale.h"
#include "../Common/common.h"

int Sale_Perst_Insert(const sale_t *data);
int Ticket_Perst_Update(int saleID);


#endif