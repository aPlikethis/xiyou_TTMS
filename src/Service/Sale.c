#include "Sale_UI.h"
#include "Seat_UI.h"

#include "../Persistence/Play_Persist.h"
#include "../Persistence/Sale_Persist.h"
#include "../Persistence/EntityKey_Persist.h"

#include "../Service/play.h"
#include "../Service/schedule.h"
#include "../Service/seat.h"
#include "../Service/account.h"
#include "../Service/Ticket.h"
#include "../Service/Sale.h"
#include "../Service/Studio.h"

#include "../Common/List.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>

static const int PLAY_PAGE_SIZE = 5;
static const int SCHEDULE_PAGE_SIZE = 5;

//根据剧目ID显示演出计划
void Sale_UI_MgtEntry()
{
    int id,i;
    char choice;

    play_list_t head;
    play_node_t *pos;
    Pagination_t paging;

    List_Init( head , play_node_t);
    Play_Srv_FetchAll(head);

    paging.offset = 0;
	paging.pageSize = PLAY_PAGE_SIZE;

	paging.totalRecords = Play_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	do{
        printf("\n=================================================================================================\n");
        printf("**************************************** 显 示 剧 目 ********************************************\n\n\n");
        printf("%4s %10s %10s %10s %10s %14s %8s\n\n\n", "剧目编号", "剧目名称",
                        "出品地区","剧目时长","上映日期","下线日期","票价");
        printf("-------------------------------------------------------------------------------------------------\n");
        //
        Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i){
            printf("%4d %10s %10s %10d ", pos->data.id,
						pos->data.name, pos->data.area, pos->data.duration);
            printf("%10.4d/%.2d/%.2d  %8.4d/%.2d/%.2d  %4d\n\n\n",pos->data.start_date.year,pos->data.start_date.month,pos->data.start_date.day,pos->data.offline_date.year,pos->data.offline_date.month,pos->data.offline_date.day,pos->data.price);
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~ 总页数:%2d ~~~~~~~~~~~~~~~~~~~~~~~~~~ 当前页 %2d/%2d ~~~~~~~~~~~~~~~~~~~~~\n\n",
					paging.totalRecords, Pageing_CurPage(paging),
					Pageing_TotalPages(paging));
        printf("*************************************************************************************************\n");
        printf("              P   上一页   |   N   下一页   |   C   显示演出计划   |   R   返回上层");
        printf("\n=================================================================================================\n");
        printf("请输入您的选择:");
        fflush(stdin);
        scanf("%c", &choice);
        getchar();

        switch (choice) {
		case 'c':
		case 'C':
		    printf("请输入剧目ID:");
		    scanf("%d",&id);
		    system("cls");
            while(!Play_Srv_FetchByID( id , &head->data))
            {
                printf("不存在该剧目,请重新输入剧目ID:\n");
                scanf("%d",&id);
            }

            Sale_UI_ShowScheduler(id);
            paging.totalRecords = Play_Srv_FetchAll(head);
            List_Paging(head, paging, play_node_t);
		    break;
        case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
			}
			break;
        }
    }while (choice != 'r' && choice != 'R');
    system("cls");
    //释放链表空间
	List_Destroy(head, play_node_t);
}


//根据playID显示演出计划
void Sale_UI_ShowScheduler(int playID)
{
    int i, id;
	char choice;

    schedule_t *temp;
	schedule_list_t head;
	schedule_node_t *pos;

	play_t  buf;

	Pagination_t paging;
	temp = (schedule_t*)malloc(sizeof(schedule_t));

    Play_Perst_SelectByID(playID, &buf);

	List_Init(head, schedule_node_t);
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

    //判断所有演出计划中的剧目ID中，是否有传进来参数ID
    //如果有则显示演出计划
    //否则输出没有与该剧目相关的演出计划


	do {
		printf(
				"\n=================================================================================================\n");
		printf(
				"************************************* 该 剧 目 的 演 出 计 划 ***********************************\n\n\n");
		printf( "%5s  %10s  %10s  %10s %8s\n\n\n", "演出计划编号", "上映剧目名称", "演出厅编号",
				"放映日期", "放映时间" );
		printf( "-------------------------------------------------------------------------------------------------\n");
		//显示数据
		Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i){
		    if(pos->data.play_id == playID){

                printf("%5d  %10s  %10d ", pos->data.id, buf.name ,pos->data.studio_id);
                printf("%12.4d/%.2d/%.2d  ",pos->data.date.year,pos->data.date.month,pos->data.date.day);
                printf("%8.2d:%.2d:%.2d  \n",pos->data.time.hour,pos->data.time.minute,pos->data.time.second);
		    }
		}
		printf("~~~~~~~~~~~~~~~~~~~~~~ 总页数:%2d ~~~~~~~~~~~~~~~~~~~~~~~~~~~ 当前页 %2d/%2d ~~~~~~~~~~~~~~~~~~~~\n\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("*************************************************************************************************\n");
		printf("        P   上一页    |    N    下一页    |    S    显示所有票信息    |    R    返回上层");
		printf("\n=================================================================================================\n");
		printf("请输入您的选择:");
		fflush(stdin);
		scanf("%c", &choice);
		getchar();
		switch (choice) {

        case 's':
        case 'S':
            printf("请输入您想要的演出计划编号:\n");
            scanf("%d",&id);
            system("cls");
            while(!Schedule_Srv_FetchByID(id , temp))
            {
                printf("不存在该演出计划,请重新输入:\n");
                scanf("%d",&id);
            }
            Sale_UI_ShowTicket(id);
            break;
		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	system("cls");
	free(temp);
	//释放链表空间
	List_Destroy(head, schedule_node_t);
}


//根据计划ID，显示演出票
void Sale_UI_ShowTicket(int schID)
{
    char choice;
    int i;

    schedule_t *schedule;
    seat_list_t seat;
    ticket_list_t head;
    ticket_node_t *pos;
    Pagination_t paging;

    schedule = (schedule_t*)malloc(sizeof(schedule_t));
    List_Init(seat,seat_node_t);
    List_Init(head,ticket_node_t);
    paging.offset = 0;
	paging.pageSize = 8;

    paging.totalRecords = Ticket_Srv_FetchAll(head,schID);
    Paging_Locate_FirstPage(head, paging);
    do{
        printf("\n=================================================================================================\n");
        printf("***************************************** 演 出 票 清 单 ****************************************\n\n\n");
        printf("%10s %10s %10s %10s %14s\n\n\n", "演出票ID", "演出计划ID",
                        "座位ID","票价","当前票的状态");
        printf("-------------------------------------------------------------------------------------------------\n");
        //
        Paging_ViewPage_ForEach(head, paging, ticket_node_t, pos, i){
            printf("%10d %10d %10d %10d %14d\n", pos->data.id,pos->data.schedule_id,pos->data.seat_id,pos->data.price, pos->data.status);
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~~ 总页数:%2d ~~~~~~~~~~~~~~~~~~~~~~~ 当前页 %2d/%2d ~~~~~~~~~~~~~~~~~~~~~~~\n\n",
                paging.totalRecords, Pageing_CurPage(paging),
                Pageing_TotalPages(paging));
        printf(" [0] 待售 | [1] 已售 | [9] 预留\n");
        printf("*************************************************************************************************\n");
        printf("            P     上一页    |     N     下一页    |     B    购票    |    R    返回上层");
        printf("\n=================================================================================================\n");

        printf("请输入您的选择:");
        fflush(stdin);

        scanf("%c", &choice);
        getchar();
        switch(choice){
            case 'b':
			case 'B':
			    system("cls");
			    Schedule_Srv_FetchByID(schID,schedule);
                Seat_Srv_FetchByRoomID(seat,schedule->studio_id);
				Sale_UI_SellTicket(head,seat,schedule->studio_id);
				break;
            case 'p':
			case 'P':
				if (!Pageing_IsFirstPage(paging)) 	//上一页
				{
					Paging_Locate_OffsetPage(head, paging, -1, ticket_node_t);
				}
				break;
			case 'n':
			case 'N':
				if (!Pageing_IsLastPage(paging)) 	//下一页
				{
					Paging_Locate_OffsetPage(head, paging, 1, ticket_node_t);
				}
				break;
        }
    }while (choice != 'r' && choice != 'R');
    system("cls");
		//释放链表
    List_Destroy(head, ticket_node_t);
    List_Destroy(seat,seat_node_t);

}

//售票
int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList, int studioID)
{
    int x,y;
    studio_t studioRec;
    seat_node_t *seatRec;
    ticket_node_t *ticketRec,*ticketTemp;

    Studio_Srv_FetchByID(studioID, &studioRec);


    printf("\n==================================================================================================\n");
    printf("************************************  演 出 厅 座 位 信 息  **************************************\n");
    printf("--------------------------------------------------------------------------------------------------\n\n\n");
    seat_node_t *seatdata;
    int i,j;
    printf("               ");
    for(j = 1; j <= studioRec.colsCount; j++ )
        printf("%2d ",j);
    printf("\n");
    for (i = 1; i <= studioRec.rowsCount; i++)
    {
        j=1;
        printf("  \t%2d排: ", i);
        List_ForEach(seatList,seatdata)
        {
            if (seatdata->data.row == i)
            {
                while (seatdata->data.column != j && j <= studioRec.colsCount) {
                    printf("%3c", ' ');
                    j++;
                }
                ticketTemp = Ticket_Srv_FetchBySeatID(tickList,seatdata->data.id);
                if(ticketTemp->data.status == 0)
                    printf("%3c", Seat_UI_Status2Char(seatdata->data.status));
                else
                    printf("%3c", Seat_UI_Status2Char(9));
                j++;
            }
        }
            printf("\n");
    }
    printf("--------------------------------------------------------------------------------------------------\n\n");
    printf("                 [#] 可购      |      [X] 已售或坏座       |       [|] 过道\n");
    printf(
           "\n==================================================================================================\n");
    do
    {
        printf("请输入您的购买票的行号: ");
        scanf("%d", &x);
        printf("请输入您的购买票的列号: ");
        scanf("%d", &y);
    }while(studioRec.rowsCount<x||studioRec.colsCount<y);
    seatRec = Seat_Srv_FindByRowCol(seatList,x,y);
    ticketRec = Ticket_Srv_FetchBySeatID(tickList,seatRec->data.id);
    if(ticketRec == NULL)
    {
        printf("售票失败!\n");
        return 0;
    }
    if(ticketRec->data.status == 1 || ticketRec->data.status == 9)
    {
        printf("该票以售,请勿重复购买！\n");
        return 0;
    }
    ticketRec->data.status = 1;
    if(Ticket_Srv_Modify(&ticketRec->data))
    {
        printf("售票成功！\n");

        sale_t sale;

        sale.id=EntKey_Perst_GetNewKeys("Ticket_Sale", 1);

        user_date_t temp1;
        user_time_t temp2;
        temp1 = DateNow();
        temp2 = TimeNow();

        sale.date.day = temp1.day;
        sale.date.month = temp1.month;
        sale.date.year = temp1.day;

        sale.time.hour = temp2.hour;
        sale.time.minute = temp2.minute;
        sale.time.second = temp2.second;

        sale.ticket_id = ticketRec->data.id;
        sale.user_id = gl_CurUser.id;
        sale.value = ticketRec->data.price;
        sale.type = 1;
        Sale_Srv_Add(&sale);
        return 1;
    }
    else
    {
        printf("售票失败!\n");
        return 0;
    }

}


//退票
void Sale_UI_ReturnTicket()
{
    int id;
    ticket_t temp;

    printf("请输入票的ID：\n");
    scanf("%d",&id);
    if(!Ticket_Srv_FetchBySchID( id, &temp))
    {
        printf("没有找到相应的票!\n请按 [Enter] 返回!\n");
        getchar();
        getchar();
        return ;
    }
    else
    {
        if(temp.status==0)
        {
            printf("该票还没有售出，无法退票！\n");
        }
        if(temp.status==1)
        {
            temp.status = 0;
            Ticket_Srv_Modify(&temp);
            sale_t refound;

            refound.id=EntKey_Perst_GetNewKeys("Ticket_Refound", 1);

            user_date_t temp1;
            user_time_t temp2;
            temp1 = DateNow();
            temp2 = TimeNow();

            refound.date.day = temp1.day;
            refound.date.month = temp1.month;
            refound.date.year = temp1.day;

            refound.time.hour = temp2.hour;
            refound.time.minute = temp2.minute;
            refound.time.second = temp2.second;

            refound.ticket_id = temp.id;
            refound.user_id = gl_CurUser.id;
            refound.value = -temp.price;
            refound.type = -1;

            Sale_Srv_Add(&refound);
            printf("退票成功！\n");
        }
    }
}
