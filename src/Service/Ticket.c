#include "../Common/List.h"
#include "../Common/common.h"

#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "../Service/Sale.h"

#include "../Persistence/Ticket_Persist.h"
#include "../Persistence/Play_Persist.h"



//标识符：TTMS_SCU_Schedule_Srv_FetchByID
//功能: 根据ID获取演出计划
int Schedule_Srv_FetchByID(int id,schedule_t*buf )
{}


//标识符：TTMS_SCU_Ticket_Srv_GenBatch
//功能：生成演出票
void Ticket_Srv_GenBatch(int schedule_id)
{}
//标识符：TTMS_SCU_Ticket_Sry_DeleteBatch
//功能：根据演出计划ID删除演出票
void Ticket_Srv_DeleteBatch(int schedule_id)
{}

//标识符：TTMS_SCU_Ticket_Srv_FetchByID
//功能：根据ID获取演出票
int Ticket_Srv_FetchByID(int id, ticket_t *buf)
{}
