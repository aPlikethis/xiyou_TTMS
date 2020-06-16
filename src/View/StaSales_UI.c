#include "StaSales_UI.h"
#include <time.h>
#include<stdio.h>
#include "../Common/list.h"
#include "../Service/Sale.h"
#include "../Service/Account.h"
#include "../Service/SalesAnalysis.h"
#include "../Service/StaSales.h"

//外部变量gl_CurUser 用于存储登录用户信息
extern account_t gl_CurUser;

//定义分页机制中页面大小为5
static const int SALESANALYSIS_PAGE_SIZE = 5;

//统计销售额界面
void StaSales_UI_MgtEntry ()
{
    
    if(gl_CurUser.type == 1){
        StaSales_UI_Self();
        printf("please input the [Enter]");
        getchar();
    }
    else if(gl_CurUser.type== 2){
        StaSales_UI_Clerk();
        printf("please input the [Enter]");
        getchar();
    }
    else{
        printf("you can't join in there!please input the [Enter] to exit");
        getchar();
    }
}

//统计个人销售额界面
void StaSales_UI_Self()
{
    int id = gl_CurUser.id;
    char choice;
    
    ttms_date_t curdate,startdate,enddate;
    struct tm *p;
    time_t timep;
    time(&timep);
    p = localtime(&timep);

    printf("[D]ay is One-day sales            |            [M]onth Monthly sales");
    printf("\nyou choice:");
    scanf("%c",&choice);
    getchar();
	setbuf(stdin,NULL);

    curdate.year = p->tm_year + 1900;
    curdate.month = p->tm_mon + 1;
    curdate.day = p->tm_mday;
    startdate.year = p->tm_year + 1900;
    startdate.month = p->tm_mon + 1;
    startdate.day = 1;
    enddate.year = p->tm_year + 1900;
    enddate.month = p->tm_mon + 1;
    enddate.day = 31;

    switch(choice){
        case 'd':
        case 'D'://当日
        printf("Your sales this day are %d\n",StaSales_Srv_CompSaleVal(id,curdate,curdate));
        break;
        case 'm':
        case 'M'://当月
        printf("Your sales this month are %d\n",StaSales_Srv_CompSaleVal(id,startdate,enddate));
        break;
    }
}

//统计售票员销售额界面
void StaSales_UI_Clerk()
{
    account_t tem;
    int id;

    ttms_date_t startdate,enddate;

    char Usrname[20];
    printf("please input the Salesperson username:");
    scanf("%s",Usrname);
    if(Account_Srv_FetchByName(Usrname,&tem)){
        if(tem.type!=USR_CLERK){
            printf("This man is not a salesman!!");
            getchar();
            return ;
        }
        id = tem.id;
        printf("please input startdate(year month day):");
        scanf("%d%d%d",&startdate.year,&startdate.month,&startdate.day);
        printf("please input enddate(year month day):");
        scanf("%d%d%d",&enddate.year,&enddate.month,&enddate.day);
        getchar();
        printf("The salesman's sales during this period are %d\n",StaSales_Srv_CompSaleVal(id,startdate,enddate));
    }
    else{
        printf("the user is not in this company!!");
        getchar();
    }
}