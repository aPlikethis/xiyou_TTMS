#include "../View/Ticket_UI.h"
#include "../View/Sale_UI.h"

#include "../Common/List.h"
#include "../Common/common.h"

#include "../Service/Ticket.h"
#include "../Service/Play.h"
#include "../Service/studio.h"
#include "../Service/Schedule.h"
#include "../Service/seat.h"


#include <stdio.h>
#include <stdlib.h>

//标识符：TTMS_SCU_Ticket_UI_MgtEnt
//功能：显示与参数对应的演出计划信息
void Ticket_UI_MgtEntry(int schedule_id)
{
    char choice;

    //根据演出计划ID获取演出计划信息
    //从获取的信息中，使用剧目ID获取该剧目信息
    schedule_t *need_schedule;
    play_t *need_play;

    need_schedule = (schedule_t *)malloc(sizeof(schedule_t));
    need_play = (play_t *)malloc(sizeof(play_t));
    
    Schedule_Srv_FetchByID(schedule_id, need_schedule);
    Play_Srv_FetchByID( need_schedule->play_id, need_play);
    
    
    
    
    do{
        printf(
                "\n==================================================================================================\n");
        printf(
                "*********************************************票 信 息*********************************************\n");
	printf("             剧目名称             演出厅编号             演出日期             演出时间             \n\n");
		

	printf("           %-6s                 %.2d                %d/%.2d/%.2d            %.2d:%.2d:%.2d\n\n\n",
                need_play->name,need_schedule->studio_id,
                need_schedule->date.year,need_schedule->date.month,need_schedule->date.day,
                need_schedule->time.hour,need_schedule->time.minute,need_schedule->time.second);


	printf("**************************************************************************************************\n");
	printf("          |    [A]     生成该演出票    |    [D]    重新生成演出票    |     [R]     返回上层       |\n");
	printf("\n==================================================================================================\n");
	printf("请输入您的选择：");
	fflush(stdin);
	scanf("%c",&choice);
	getchar();
        if( choice=='a' || choice == 'A' || choice == 'd' || choice == 'D' || choice == 'R' || choice == 'r')
        { 
		    switch(choice)
            {
		        case 'a':
	        	case 'A':
		         	if (Ticke_Srv_GenBatch(schedule_id))
			        	printf("生成成功!\n");
			     else
				        printf("生成失败!\n");
			        break;
		        case 'd':
		        case 'D':
			        if(Ticket_Sry_DeleteBatch(schedule_id) && Ticker_Srv_GenBatch(schedule_id))
				        printf("重新生成成功");
			        else
				        printf("重新生成失败");
			        break;
            }   
        }
        else
        {
           printf("未知操作，请重新输入"); 
        }
	}while (choice != 'r' && choice != 'R');
	system("cls");

}
//标识符：TTMS_SCU_Ticket_UI_Qry
//功能：查询演出票界面
void Ticket_UI_Query(void) {
	int id;
	printf("\n\t\t\t\t\t票的ID:");
	scanf("%d",&id);
	Ticket_UI_ShowTicket(id);
}


//标识符：TTMS_SCU_Ticket_UI_ShowTickeet
//功能：查询演出票界面
int Ticket_UI_ShowTicket(int ticket_id) {
	ticket_t buf, data;
	sale_t sale;
	system("cls");
	gettime();
	printf("\n\n\n\n\n") ;
	if (Ticket_Srv_FetchByID(ticket_id, &buf))
	{
		if (buf.status == 1)
		{
			data.id = buf.id;
			data.schedule_id = buf.schedule_id;
			data.seat_id = buf.seat_id;
			data.status = 1;

			Ticket_Info(&data);
			printf("\t\t\t\t    状态:已售\n");
			printf("\n\t\t\t\t    任意键返回");
			getch();

		}
		else
		{
			data.id = buf.id;
			data.schedule_id = buf.schedule_id;
			data.seat_id = buf.seat_id;
			data.status = 1;

			Ticket_Info(&data);
			printf("\t\t\t\t    状态:未售\n");
			printf("\n\t\t\t\t    任意键返回");
			getch();


		}
	}
	else
	{
		printf("\t\t\t\t        无此票,任意键返回");
		getch();
	}
    return 0;
}
