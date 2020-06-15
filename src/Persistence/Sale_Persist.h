#ifndef SLAEINGPERSIST_H
#define SALEINGPERSIST_H

#include "../Service/Sale.h"
#include "../Common/common.h"

int Sale_Perst_Insert(const sale_t *data);
int Sale_Perst_DeleteByID(int saleID);


//根据用户ID载入给定时间区间内的销售记录
int Sale_Perst_SelectByUsrID(sale_list_t list, int usrID,
		ttms_date_t stDate, ttms_date_t endDate);

//根据用户ID载入给定时间区间内的销售记录
int Sale_Perst_SelectByDate(sale_list_t list,
		ttms_date_t stDate, ttms_date_t endDate);


#endif