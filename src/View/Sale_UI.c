#include "Play_UI.h"
#include "Schedule_UI.h"
#include "Ticket_UI.h"
#include "Account_UI.h"
#include "MaiAccount_UI.h"
#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Service/Sale.h"
#include "../Persistence/EntityKey_Persist.h"
#include "../Common/Common.h"
#include "Main_Menu.h"
#include "Studio_UI.h"
#include "StaSales_UI.h"
#include "../Service/Schedule.h"
#include "../Service/Account.h"
#include "../Service/Play.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Common/ComFunction.h"
#include "../View/Ticket_UI.h"
#include "../Service/SalesAnalysis.h"
#include "../Common/List.h"
#include <time.h>
#include "../Service/Account.h"


int List_Foreach(ticket_list_t list,int id);
void Ticket_UI_Print(const ticket_t data);

//int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList){
//
//	int id;
//	ticket_list_t head;
//	schedule_t sch;
//
//
//	printf("\t\t\t请输入演出计划的ID:");
//
//	while(1){
//					if(scanf("%d",&id)==1){ cl_stdin(); break;}
//					else{ cl_stdin(); printf("\t\t\t您的输入有误！请重新输入:"); }
//	}
//
//	if(!Schedule_Srv_FetchByID(id, &sch)){
//			printf("\n\t\t\t未找到ID为%d的演出计划，按任意键返回 。。。",id);
//			getchar();
//			getchar();
//			return 0;
//	}
//
//	Ticket_Srv_FetchBySchID(tickList, sch.id);
//
//	Seat_Srv_FetchValidByRoomID(seatList, sch.studio_id);
//
//
//	Ticket_UI_ListBySch(&sch,tickList,seatList);
//
//
//    return 1;
//}


int Sale_UI_SellTicket(ticket_list_t list_t,seat_list_t list_s)
{
    seat_node_t * seat = NULL;
    sale_t data_t ;
    int row,col;
    while(1)
    {
        printf("please input the row you want to buy :");
        scanf( "%d",&row);
        printf("please input the col you want to buy :");
        scanf( "%d",&col);
        getchar( );
        seat = Seat_Srv_FindByRowCol(list_s,row,col);

        if(NULL == seat)
        {
            printf( "the seat is not exit!\n");
            continue;
        }

        if(seat->data.status == '@')
        {
            printf("the seat is broken!\n\n");
        }
        else if(seat->data.status == ' ')
        {
            printf("the seat is empty!!\n");
        }
        else
        {
            break;
        }
    }

    ticket_t buf;
    account_t buf_a;

    Ticket_Srv_FetchBySeatID(seat->data.id,&buf);
    if(buf.status == 1)
    {
        printf( "the ticket is Sale!\n");
        return 0;
    }
    else
    {
        data_t.ticket_id = buf.id;
//        List_Foreach(list_t,buf.id);
        buf.status = 1;
        Ticket_Srv_Modify(&buf);
        data_t.user_id = gl_CurUser.id;
        data_t.type = 1;
        data_t.value = buf.price;
        struct tm *p;
        time_t timep;
        time(&timep);
        p = localtime(&timep);
        data_t.date.year = p->tm_year + 1900;
        data_t.date.month = p->tm_mon + 1;
        data_t.date.day = p->tm_mday;
        data_t.time.hour = p->tm_hour;
        data_t.time.minute = p->tm_min;
        data_t.time.second = p->tm_sec;
        Sale_Srv_Add(&data_t);

        Ticket_UI_Print(buf);
    }

}

int List_Foreach(ticket_list_t list,int id)
{
    while(1)
    {
        if(list->data.id == id)
        {
            list->data.status = 1;
            break;
        }
        else
        {
            list = list->next;
        }
    }
}


void Ticket_UI_Print(const ticket_t data)
{
    printf("your ticket data : \n");
    printf( "Ticket ID      Schedule ID    Saet ID  Price\n");
    printf( "%d                  %d           %d      %d    \n",data.id,data.schedule_id,data.seat_id,data.price);
    printf( "---------------------------------------\n");
    getchar( );
}










//根据剧目ID显示演出计划
void Sale_UI_ShowScheduler(int playID) {
	int i, id, schedule_id;
	char choice;
	
	play_t pdata;
	ticket_list_t tickList;
	seat_list_t   seatList;
	schedule_t sch_buf;
	schedule_list_t head;
	schedule_node_t *p;
	Pagination_t paging;
	
	Play_Srv_FetchByID(playID, &pdata);
	
	List_Init(head, schedule_node_t);
	
	paging.offset = 0;
	paging.pageSize = 5;

	//载入数据
	paging.totalRecords = Schedule_Srv_SelectByPlayID(playID, head);
	
	Paging_Locate_FirstPage(head, paging);

	do {
        system("cls");
        printf("user: %s | id: %d \n", gl_CurUser.username, gl_CurUser.id);
		printf("\n\t\t\t==================================================================\n");
		printf("\t\t\t      \t\t\tPlay：%10s Schedules\n",pdata.name);

		printf("\t\t\t%5s \t %-5s\t%-8s \t %-10s \t %-10s \t %-10s \n", "id", "playname", "schedule",
				 "play date","play time","seat count");
		printf("\t\t\t------------------------------------------------------------------\n");
		
		if(!List_IsEmpty(head)){
			//显示数据
			Paging_ViewPage_ForEach(head, paging, schedule_node_t, p, i){
			    if(p == NULL) {
                    break;
			    }
				printf("\t\t\t%5d %5d %5d ", p->data.id, p->data.play_id,p->data.studio_id);
			
				printf("\t%4d-%02d-%02d ",p->data.date.year, p->data.date.month, p->data.date.day);
				printf("\t%2d:%02d ", p->data.time.hour, p->data.time.minute);
				printf("\t%5d\n", p->data.seat_count);
			}
		}else{
		
			printf("\t\t\t暂无数据！\n");
		}

		printf("\n\t\t\t------------ %2d totalrecords-------------------- %2d/%2d page---------------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t\t******************************************************************\n");
		printf("\t\t\t[P]last page             |    [N]ext page             |     [R]eturn\n");
		printf("\t\t\t[S]enter sale system\n");
		printf("\n\t\t\t==================================================================\n");
		printf("\t\t\tinput your choice:");
		
		choice=l_getc();
	

		switch (choice) {
		
//		case 'u':
//		case 'U':
//
//				printf("\t\t\t请输入要修改演出计划的ID:");
//
//				while(1){
//					if(scanf("%d",&id)==1){ cl_stdin(); break;}
//					else{ cl_stdin(); printf("\t\t\t您的输入有误！请重新输入:"); }
//				}
//
//
//			break;
			
		case 's':
		case 'S':
			{
				
				printf("please input schedule id:");
				scanf("%d", &schedule_id);
				Schedule_Srv_FetchByID(schedule_id, &sch_buf);
				List_Init(tickList, ticket_node_t);
				List_Init(seatList,   seat_node_t);
				Seat_Srv_FetchByRoomID(seatList, sch_buf.studio_id);
				
			
			
				Sale_UI_SellTicket(tickList,seatList);
				
				List_Destroy(tickList, ticket_node_t);
				List_Destroy(seatList,   seat_node_t);
			}
			break;
			
		case 't':
		case 'T':
			//();
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
	//释放链表空间
	List_Destroy(head, schedule_node_t);
}


void Sale_UI_MgtEntry(void)
{
//    if(gl_CurUser.type==USR_ANOMY||gl_CurUser.type==USR_ADMIN){
//        printf("you can't join in there!please input the [Enter]");
//        getchar();
//        return 0;
//    }
    system("clear");
    char choice;
    char name[20];
    int i;
    int play_id;
    play_node_t *pos;


    play_list_t list;
    play_list_t list_fetch;
    List_Init(list,play_node_t);
    List_Init(list_fetch,play_node_t);

    Pagination_t paging;
    paging.offset = 0;
    paging.pageSize = 5;
    Play_Srv_FetchAll(list_fetch);
    paging.totalRecords = Play_Srv_FetchAll(list);     //获取全部 剧目 信息
    Paging_Locate_FirstPage(list,paging);

    do
    {
        system("cls");
        printf("user: %s | id: %d \n", gl_CurUser.username, gl_CurUser.id);
        printf(
                "\n======================================================================================\n");
        printf(
                "***************************** Projection Play List ***********************************\n");

        printf( "%5s %15s %5s %10s %3s %3s %10s %10s     %3s\n","ID","NAME","TYPE","AREA","RATING","DURATION","STARTDATA","ENDDATA","PRICE");
        printf( "--------------------------------------------------------------------------------------\n");

        Paging_ViewPage_ForEach(list,paging,play_node_t,pos,i)
        {
            if(pos == NULL) {
                break;
            }
            printf( "%5d %15s %5d %10s %6d %6d %7d%3d%3d %4d%3d%3d     %4d\n",pos->data.id,pos->data.name,pos->data.type,pos->data.area,pos->data.rating,pos->data.duration,pos->data.start_date.year,pos->data.start_date.month,pos->data.start_date.day,pos->data.end_date.year,pos->data.end_date.month,pos->data.end_date.day,pos->data.price);
        }


        printf( "----------------Total Recoeds: %2d---------------------------Page %2d   %2d   -----------\n",paging.totalRecords,Pageing_CurPage(paging),Pageing_TotalPages(paging));

        printf("**************************************************************************************\n");


        printf( "[C]show Schedule      [S]find play name    [f]      [P]rev       [N]ext         [R]eturn          \n");
        printf( "======================================================================================\n");
        printf("please input your choice : ");
        setbuf(stdin,NULL);
        scanf( "%c",&choice);
        getchar( );
        switch(choice)
        {
            case'c':
            case'C':
                printf( "please input play_id  :");
                scanf( "%d",&play_id);
                getchar( );
                Sale_UI_ShowScheduler(play_id);
                break;
            case's':
            case'S':
                printf( "please input the Play_ name :");
                setbuf(stdin,NULL);
                gets(name);
                system("clear");
                Schedule_Srv_SelectByName(name);
//                Play_Srv_Print(list_fetch,name);
                break;
            case 'f':
 //           case 'F':
 //               printf( "please input the Play_ name :");
//              Play_Srv_FetchByName(list_fetch,name);
  //              break;
            case'n':
            case'N':
                if(!Pageing_IsLastPage(paging))
                {
                    Paging_Locate_OffsetPage(list, paging, 1, play_node_t);
                }
                break;
            case'P':
            case'p':
                if(!Pageing_IsFirstPage(paging))
                {
                    Paging_Locate_OffsetPage(list, paging,-1, play_node_t);
                }
                break;

        }

    }while(choice != 'r' && choice != 'R');


}


//退票
void Sale_UI_ReturnTicket(){
	char choice;
	int t=0;

		sale_node_t *sale_buf;
		sale_list_t list;
		ticket_t buf;
		schedule_t scd;
		List_Init(list, sale_node_t);

		if( Sale_Srv_FetchByUserID(gl_CurUser.id, list) ) {
		    List_ForEach(list, sale_buf) {
		        if(sale_buf == NULL) {
                    break;
		        }
                if (Ticket_Srv_FetchByID(sale_buf->data.ticket_id, &buf)) {
                    Schedule_Srv_FetchByID(buf.schedule_id, &scd);
                    if (buf.status == TICKET_SOLD) {
                        Ticket_UI_Print(buf);
                        user_time_t nowtime = TimeNow();
                        if (DateCmp(DateNow(), scd.date) == -1 ||
                            (DateCmp(DateNow(), scd.date) == 0 && scd.time.hour < nowtime.hour &&
                             scd.time.minute < nowtime.minute)) {
                            t = 1;
                            Ticket_UI_Print(buf);
                        } else {
                            printf("\n\t\t\tThe ticket has expired and cannot be refunded");
                            printf("\n\n\t\t\tPress any key to continue!...\n");
                            getchar();
                        }
                    } else {

                        printf("\n\t\t\tThe ticket does not exist or is not sold and cannot be refunded");
                        printf("\n\n\t\t\tPress any key to continue!...\n");

                        getchar();
                    }
                }
            }
        }
		else {
		    printf("you don't have ticket\n");
		}
		
		
		if(t){
			printf("\t\t\t\n Please input Q to confirm the refund input r to return:");
			choice=l_getc();
			if('r'==choice || 'R'==choice) {
			if('q'==choice || 'Q'==choice) {
			
				
	       			buf.status=TICKET_AVL;
	       			sale_t data;
	       					
	       			data.id=EntKey_Srv_CompNewKey("sale");
	       			data.user_id=gl_CurUser.id;
	       			data.ticket_id=buf.id;
	       			data.date=DateNow();
	       			data.time=TimeNow();
	       			data.value=buf.price;
	       			data.type=SALE_RETURN;
	       					
	       			Sale_Srv_Add(&data);
	       					
//	       			Ticket_Srv_Modify(&buf);
       					
       				printf("\n\t\t\tRefund succeeded!");
       				printf("\n\n\t\t\tPress any key to continue!...\n");
				cl_stdin();
				getchar();
       			}	
			}		
       		}
}

