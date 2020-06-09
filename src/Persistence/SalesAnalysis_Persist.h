#ifndef SALESANALYSIS_PERSIST_H_
#define SALESANALYSIS_PERSIST_H_

#include "../Service/Sale.h"
#include "../Service/SalesAnalysis.h"
#include "../Service/Play.h"

int Salesanalysis_Perst_Insert(const salesanalysis_t *data);
int SalesAnalysis_Perst_SelectAll(salesanalysis_list_t list);
int Sale_Perst_SelectALL(sale_list_t list);

#endif