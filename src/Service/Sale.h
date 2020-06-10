#ifndef SALE_H_
#define SALE_H_
#include "../Common/common.h"
#include "Account.h"
#include "Ticket.h"

typedef enum{
	SALE_SELL=1,	//买票
	SALE_RETURN=-1	//退票
}sale_type_t;
//售票信息
typedef struct {
    
    }sale_t;

typedef struct sale_node {
	sale_t data;
	struct sale_node *next, *prev;
} sale_node_t, *sale_list_t;

//根据票的信息插入到订单的信息
int Sale_Srv_Add(const sale_t *data);

//删除订单的信息
int Sale_Srv_DeleteByID(int saleID);

int Sale_Srv_selectByTime(char querytime[][30], sale_list_t head);

int Sale_Srv_SelectByUid(char *queryuid, sale_list_t head);

#endif