#include <stdio.h>
#include <string.h>
#include "SalesAnalysis_UI.h"
#include "../Common/list.h"
#include "../Common/common.h"
#include "../Service/SalesAnalysis.h"

//外部变量gl_CurUser 用于存储登录用户信息
extern account_t gl_CurUser;


//剧院销售排行函数，降序显示




void SalesAanalysis_UI_MgtEntry()
{
    do{
        printf("\t\t\t===============================================\n");
		printf("      \t\t\t[B]剧目票房排行榜\n");
        printf("      \t\t\t[D]查询员工在给定日期区间销售额情况\n");
		printf("      \t\t\t[S]查询员工在给定日期区间售票情况\n");
		printf("\n\t\t\t***********************************************\n");
		printf("\t\t\t[R]返回\n");
		printf("\t\t\t===============================================\n");
		printf("\t\t\t请选择功能：");
        fflush(stdin);
		scanf("%c",&choice);
	    switch(choice)
        {
            case 'B':
			case 'b':

				break;
			case 'D':
			case 'd':

				break;
			case 'S':
			case 's':
				
    }while(choice!='R' && choice!='r' );
}