#include "Play_UI.h"
#include "Schedule_UI.h"
#include "Sale_UI.h"
#include "Ticket_UI.h"
#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Service/Sale.h"
#include "../Common/ComFunction.h"
#include "../Common/Common.h"
#include "Main_Menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//引用登陆用户的全局数据结构
extern account_t gl_CurUser;

//根据计划ID，显示演出票
int Sale_UI_ShowTicket(int schID)
{
	seat_list_t list;
	List_Init(list,seat_node_t);
	int studio_ID;
	
	printf( "please input the studio ID :");
	scanf( "%d",&studio_ID);
	getchar( );
	int seat = Seat_Srv_FetchValidByRoomID(list,studio_ID);
	
	int i;
	char choice;
	ticket_node_t *pos;
	Pagination_t paging;

//	List_Init(list,seat_node_t);
	paging.offset = 0;
	paging.pageSize = TICKET_PAGE_SIZE;
	ticket_list_t list_ti;
	
	List_Init(list_ti,ticket_node_t);

	paging.totalRecords = Ticket_Srv_FetchBySchID_ticket(list_ti,schedule_id);
	Paging_Locate_FirstPage(list_ti,paging);
	studio_t buf;
	do
	{
		system("clear");
	//	paging.totalRecords = Ticket_Srv_FetchBySchID(schedule_id,list_ti);
	//
	//
		printf( "====================================================================================\n");
		printf( "*****************************************Ticket*************************************\n");
		printf( "------------------------------------------------------------------------------------\n");
        printf( "Ticket ID          Scheuid ID         Seat ID       Price             Ticket Status\n");
		Paging_ViewPage_ForEach(list_ti,paging,ticket_t,pos,i)
		{
			printf("  %5d               %5d            %5d      %5d                     %5d\n",pos->data.id,pos->data.schedule_id,pos->data.seat_id,pos->data.price,pos->data.status);
		}

		printf( "------Total Records  : %2d ------------------------Page %2d / %2d----------------------\n",paging.totalRecords,Pageing_CurPage(paging),Pageing_TotalPages(paging));
		Studio_Srv_FetchByID(studio_ID,&buf);

		int xx = 0,yy = 1;		
			for(int i=0; i <= buf.rowsCount;i++)
        	{
	            for(int j=0;j<=buf.colsCount;j++)
        	    {
                	if(i==0)
			{
        	            printf("%3d",xx++);
                	}
	                else if(j==0)
			{
                	    printf("%3d",yy++);
	                }
        	        else
			{
				int flag;
				flag=0;
				    List_ForEach(list_ti,pos)
		            {
					//	printf("status =%d \n",pos->data.status);
                //printf("seatid = %d\n",pos->data.seat_id);
						seat_node_t *buf1;
						buf1  =  Seat_Srv_FindByID(list, pos->data.seat_id);
						//Seat_Srv_FetchByID(pos->data.seat_id, buf1);
						//printf("row = %d  col =  %d pos-sss = %d \n",buf1->data.row,buf1->data.column,pos->data.status);
					    if(buf1->data.row ==i && buf1->data.column == j)
					    {
							if(pos->data.status==0){
									printf( "%3c",'#');
									flag = 1;
							}
							else{
								flag = 1;
								printf("   ");
							}
							//printf("status   =%d  \n",pos->data.status);
				 	   }
					}if(!flag) printf("   ");
				} 
		 	}
		    putchar('\n');
		}

		printf( "[N]ext    [P]rev    [S]ale Ticket      [R]eturn    \n");


		printf( "Your choice:");
		choice = getchar();
		//scanf( "%c",&choice);
		getchar( );
		
		switch(choice)
		{

			case'n':
			case'N':
				if (!Pageing_IsLastPage(paging)) 
				{
					Paging_Locate_OffsetPage(list_ti, paging, 1, ticket_node_t);
				}

				break;
			case'p':
			case'P':
if (!Pageing_IsFirstPage(paging)) 
				{
					Paging_Locate_OffsetPage(list_ti, paging, -1,ticket_node_t);
				}
				break;
			case'S':
			case's':
				Sale_UI_SellTicket(list_ti,list);
				//paging.totalRecords = Ticket_Srv_FetchBySchID(schedule_id,list_ti);
				break;

		}

	}while(choice != 'R'  && choice != 'r');
}

    



inline int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList){
	
	int id;
	ticket_list_t head;
	schedule_t sch;
	
	
	printf("\t\t\t请输入演出计划的ID:");
			
	while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t\t您的输入有误！请重新输入:"); }
	}
	
	if(!Schedule_Srv_FetchByID(id, &sch)){
			printf("\n\t\t\t未找到ID为%d的演出计划，按任意键返回 。。。",id);
			getchar();
			getchar();
			return 0;
	}
	
	Ticket_Srv_FetchBySchID(tickList, sch.id);
			
	Seat_Srv_FetchValidByRoomID(seatList, sch.studio_id);
	
	
	Ticket_UI_ListBySch(&sch,tickList,seatList);
	
	
    return 1;
}



//根据剧目ID显示演出计划
void Sale_UI_ShowScheduler(int playID) {
	int i, id;
	char choice;
	
	play_t pdata;
	ticket_list_t tickList;
	seat_list_t   seatList;
	
	schedule_list_t head;
	schedule_node_t *p;
	Pagination_t paging;
	
	Play_Srv_FetchByID(playID, &pdata);
	
	List_Init(head, schedule_node_t);
	
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Schedule_Srv_FetchByPlay(head,playID);
	
	Paging_Locate_FirstPage(head, paging);

	do {
		system("cls");
		printf("\n\t\t\t==================================================================\n");
		printf("\t\t\t      \t\t\t剧目：%10s 的演出计划 列表\n",pdata.name);

		printf("\t\t\t%5s \t %-5s\t%-8s \t %-10s \t %-10s \t %-10s \n", "计划", "剧目", "演出厅",
				 "放映日期","放映时间","座位数");
		printf("\t\t\t------------------------------------------------------------------\n");
		
		if(!List_IsEmpty(head)){
			//显示数据
			Paging_ViewPage_ForEach(head, paging, schedule_node_t, p, i){
				printf("\t\t\t%5d %5d %5d ", p->data.id, p->data.play_id,p->data.studio_id);
			
				printf("\t%4d-%02d-%02d ",p->data.date.year, p->data.date.month, p->data.date.day);
				printf("\t%2d:%02d ", p->data.time.hour, p->data.time.minute);
				printf("\t%5d\n", p->data.seat_count);
			}
		}else{
		
			printf("\t\t\t暂无数据！\n");
		}

		printf("\n\t\t\t------------ 共 %2d 项-------------------- %2d/%2d 页---------------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t\t******************************************************************\n");
		printf("\t\t\t[P]上页             |    [N]下页             |     [R]返回\n");
		printf("\t\t\t[S]进入售票系统\n");
		printf("\n\t\t\t==================================================================\n");
		printf("\t\t\t选择功能:");
		
		choice=l_getc();
	

		switch (choice) {
		
		case 'u':
		case 'U':
			
				printf("\t\t\t请输入要修改演出计划的ID:");
			
				while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t\t您的输入有误！请重新输入:"); }
				}
			
				
			break;
			
		case 's':
		case 'S':
			{
				
				
				
				List_Init(tickList, ticket_node_t);
				List_Init(seatList,   seat_node_t);
				
				
			
			
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


void Sale_UI_MgtEntry() {
	int i, id;
	char choice;

	play_list_t head;
	play_node_t *p;
	Pagination_t paging;

	List_Init(head, play_node_t);
	
	paging.offset = 0;
	paging.pageSize = PLAY_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Play_Srv_FetchAll(head);
	
	Paging_Locate_FirstPage(head, paging);

	do {
		system("cls");
		printf("\n\t\t\t==================================================================\n");
		printf("\t\t\t      \t\t\t剧目 列表\n");
		printf("\t\t\t%2s  %-10s\t%-8s  %-5s %-10s \t %-10s \t %-5s \n", "ID", "名称", "地区",
				"时长", "上映日期","下线日期","票价");
		printf("\t\t\t------------------------------------------------------------------\n");
		
		
		//显示数据
		Paging_ViewPage_ForEach(head, paging, play_node_t, p, i){
			printf("\t\t\t%2d  %-10s %-10s %-5d ", p->data.id, p->data.name,p->data.area, p->data.duration);
			printf("%4d-%02d-%02d ", p->data.start_date.year, p->data.start_date.month, p->data.start_date.day);
			printf("\t%4d-%02d-%02d ",p->data.end_date.year, p->data.end_date.month, p->data.end_date.day);
			printf("\t%-5d\n", p->data.price);
		}

		printf("\n\t\t\t----------- 共 %2d 项 ------------------- %2d/%2d 页  ----------------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t\t ******************************************************************\n");
		printf("\t\t\t        [P]上页        |            [N]下页\n\n");
		printf("\n\t\t\t[A]根据剧目ID列出演出计划                                 [R]返回\n");
		printf("\n\t\t\t==================================================================\n");
		printf("\t\t\t请选择:");
		
		choice=l_getc();
	

		switch (choice) {
		case 'a':
		case 'A':
				
				printf("\t\t\t请输入要浏览演出计划的 剧目ID:");
				while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
				}
				Sale_UI_ShowScheduler(id);
			
				break;
		/*
		case 'u':
		case 'U':
			
			
			break;
			
		
		*/
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
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, play_node_t);
}

//退票
void Sale_UI_RetfundTicket(){
	char choice;
	//int id,t=0;
     //while(1){
		system("cls");
       	//printf("\n\n\n\n");
       	printf("\n\t\t\t==================================================================\n");
       	printf("\t\t\t      \t\t\t退   票\n");
       	printf("\n\t\t\t==================================================================\n");
       	printf("\t\t\t\t\t本影院的票一但售出，拒不退回");
       	printf("\t\t\t\t按[R]返回");
       	getchar();
       	getchar();
       	Main_Menu();