#include "../View/Ticket.UI.h"

#include "../Common/List.h"

#include "../Service/Ticket.h"
#include "../Service/Studio.h"
#include "../Service/Play.h"

#include <stdio.h>


void Ticket_UI_MgtEntry(int schedule_id)
{
    do{
        printf(
                "\n==================================================================================================\n");
        printf(
                "*********************************************票 信 息*********************************************\n");
        printf("%5s  %13s  %13s  %10s\n\n", "剧目名称", "演出厅编号", "演出日期","演出时间");
    }
}
