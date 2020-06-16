#include "../Persistence/Sale_Persist.h"
#include "../Persistence/Query_Persist.h"
#include "../Service/Sale.h"
#include <assert.h>
#include <stdlib.h>
#include "../Common/List.h"
//根据票的信息插入到订单的信息
int Sale_Srv_Add(const sale_t *data) {
	return Sale_Perst_Insert(data);
}


//删除订单的信息


//int Ticket_Srv_Modify(const ticket_t*data){
//    assert(NULL!=data);
//	FILE *fp=fopen(SALE_SELL,"ab");
//	int rtn=0;
//	if (NULL==fp)
//	{
//		printf("无法打开文件 %s!\n", SALE_SELL);
//		return 0;
//	}
//	rtn=fwrite(data,sizeof(sale_t),1,fp);
//	fclose(fp);
//	return rtn;
//}
//int Ticket_Srv_Mod(const ticket_t*data){
//    assert(NULL!=data);
//	FILE *fp=fopen(SALE_SELL,"ab");
//	int rtn=0;
//	if (NULL==fp)
//	{
//		printf("无法打开文件 %s!\n", SALE_SELL);
//		return 0;
//	}
//	rtn=fwrite(data,sizeof(sale_t),1,fp);
//	fclose(fp);
//	return rtn;
//}
int Ticket_Srv_FetchBySchID(int ID,ticket_list_t list){
    return  Ticket_Perst_SelectBySchID(ID, list);

}


//ticket_node_t* Ticket_Srv_FetchBySeatID(ticket_list_t list,int seat_id)
//{
//    assert(NULL!=list);
//	ticket_node_t *p;
//
//	if (p->data.id==seat_id)
//		return p;
//    else
//	return NULL ;
//}

int Sale_Srv_FetchByUserID(int user_id, sale_list_t list) {
    return Sale_Perst_selByUserId(user_id, list);
}
