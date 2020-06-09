#include <stdio.h>
#include <string.h>
#include "SalesAnalysis.h"
#include "../Persistence/Sale_Persist.h"
#include "../Persistence/SalesAnalysis_Persist.h"
#include "Sale.h"
#include "Ticket.h"
#include "Play.h"
#include "Schedule.h"
#include "../Common/list.h"

//计算员工usrID在给定时间区间的销售额，返回销售额
int Salesanalysis_Srv_CompSaleVal(int usrID, ttms_date_t stDate, ttms_date_t endDate)
{

}

//结合剧目Play.dat,统计销售数据，构建销售分析salesanalysis_list_t list链表，返回list链表长度
int Salesanalysis_Srv_StaticSale(salesanalysis_list_t list)
{

}

//对电影票房排序
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list)
{
    
}