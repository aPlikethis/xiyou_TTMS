#ifndef STASALES_H_
#define STASALES_H_

#include "../Common/list.h"
#include "../Common/common.h"
#include "../Persistence/Sale_Persist.h"
#include "../Persistence/Account_Persist.h"

//static const int STASALES_PAGE_SIZE=5;

//根据ID获取销售额统计
int StaSales_Srv_CompSaleVal(int usrID, ttms_date_t stDate, ttms_date_t endDate);

#endif