#include "../View/Ticket.UI.h"

#include "../Common/List.h"

#include "../Service/Ticket.h"
#include "../Service/Studio.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"

#include <stdio.h>
#include <stdlib.h>

void Ticket_UI_MgtEntry(int schedule_id)
{
	char choice;
	do{
        printf(
                "\n==================================================================================================\n");
        printf(
                "*********************************************票 信 息*********************************************\n");
		printf("             剧目名称             演出厅编号             演出日期             演出时间             \n\n");
		

		printf("           %-6s                 %.2d                %d/%.2d/%.2d            %.2d:%.2d:%.2d\n\n\n");


		printf("**************************************************************************************************\n");
		printf("          |    [A]     生成该演出票    |    [D]    重新生成演出票    |     [R]     返回上层       |\n");
		printf("\n==================================================================================================\n");
		printf("请输入您的选择：");
		fflush(stdin);
		scanf("%c",&choice);
		getchar();

		switch(choice){
		case 'a':
		case 'A':
			if ()
				printf("生成成功!\n");
			else
				printf("生成失败!\n");
			break;
		case 'd':
		case 'D':
			if()
				printf("重新生成成功");
			else
				printf("重新生成失败");
			break;
		}
	}while (choice != 'r' && choice != 'R');
	system("cls");
}
