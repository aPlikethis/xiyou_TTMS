#include "../Common/List.h"
#include "../Persistence/EntityKey_Persist.h"

#include "Ticket.h"
#include "Seat.h"
#include "Sale.h"

#include "../Persistence/Ticket_Persist.h"
#include "../Persistence/Play_Persist.h"

#include <stdio.h>





int Schedule_Srv_FetchByID(int id,schedule_t*buf )
{
    return Schedule_Perst_SelectByID(id, buf);
}
void Ticket_Srv_GenBatch(int schedule_id)
{}
void Ticket_Srv_DeleteBatch(int schedule_id)
{}
int Ticket_Srv_StatRevSchID(int schedule_id,int *soldCount)
{}