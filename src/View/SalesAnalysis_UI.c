#include <stdio.h>
#include <string.h>
#include "SalesAnalysis_UI.h"
#include "../Common/list.h"
#include "../Common/common.h"
#include "../Service/Account.h"
#include "../Service/Play.h"
#include "../Service/Schedule.h"
#include "../Service/Ticket.h"
#include "../Service/SalesAnalysis.h"

//定义分页机制中页面大小为5
static const int SALESANALYSIS_PAGE_SIZE = 5;

//统计票房界面
void SalesAanalysis_UI_MgtEntry()
{
	int i;
	char choice;

	salesanalysis_list_t head;
	salesanalysis_node_t *pos;
	Pagination_t paging;//定义分页器

	List_Init(head, salesanalysis_node_t);
	paging.offset = 0;
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;

	paging.totalRecords = SalesAnalysis_Srv_StaticSale(head);
	
	SalesAnalysis_Srv_SortBySale(head);   //根据票房排序

	Paging_Locate_FirstPage(head, paging);

	do{
        system("cls");
        printf("user: %s | id: %d \n", gl_CurUser.username, gl_CurUser.id);
		printf("\t\t\t=========================================================================\n");
		printf("\t\t\t%28s""Box office chart\n");
		printf("\t\t\t-------------------------------------------------------------------------\n");
		printf("\t\t\tPlay name\t\tarea\t\tNumber of tickets sold\tbox office\tRelease time\t\tDown time\n");
		Paging_ViewPage_ForEach(head, paging, salesanalysis_node_t, pos, i){
			printf("\t\t\t%-10s\t%-10s\t%-5ld\t%-5ld\t%d-%d-%d\t%d-%d-%d\t\n",
					pos->data.name, pos->data.area, pos->data.totaltickets,pos->data.sales,
					pos->data.start_date.year,pos->data.start_date.month,pos->data.start_date.day,
					pos->data.end_date.year,pos->data.end_date.month,pos->data.end_date.day);
		}

		printf("\t\t\t---------- %2d totalRecords --------------------------- %2d/%2d page --------\n",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
		printf("\t\t\t*************************************************************************\n");
		printf("\t\t\t[P]last page	|	[N]next page	|	[R]eturn\n");
		printf("\n\t\t\t=========================================================================\n");
		fflush(stdin);
		printf("\t\t\tYour Choice:");

		scanf("%c",&choice);
		switch(choice)
		{
			case 'P':
			case 'p':
					if (!Pageing_CurPage(paging))
					{
						Paging_Locate_OffsetPage(head, paging, -1, salesanalysis_node_t);
					}
				break;
			case 'N':
			case 'n':
					if (Pageing_TotalPages(paging) > Pageing_CurPage(paging))
					{
						Paging_Locate_OffsetPage(head, paging, 1, salesanalysis_node_t);
					}
				break;
		}
	} while(choice!='R' && choice!='r');
		List_Destroy(head, salesanalysis_node_t);
}