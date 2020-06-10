#ifndef SLAEINGPERSIST_H
#define SALEINGPERSIST_H

#include "../Service/Sale.h"
#include "../Common/common.h"
//显示售票情况
int Sale_Perst_lnsert(const sale_t *data);
int Sale_Perst_DeleteByID(int saleID);
//根据用户ID载入给定时间区间内的销售记录
int Sale_Perst_SelectByUsrID(sale_list_t list,int usrID,user_date_t stDate,user_date_t endDate);
//根据时间区间载入用户ID的销售记录
int Sale_Perst_SelectByDate(sale_list_t list,
		user_date_t stDate, user_date_t endDate);

#endif