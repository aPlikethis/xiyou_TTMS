#include "Account.h"
#include "../Common/list.h"
#include "../Persistence/Account_Persist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


//创建管理员Admin匿名系统用户
void Account_Srv_InitSyS()
{
	if(Account_Perst_CheckAccFile()==1){
		return ;
	}

	system("cls");
	char pwd[20],pwd1[20];
    char ch;
    int i;
    account_t data_admin;
    printf("It is no Account.dat,please init admin!!please input [E]nter");
	setbuf(stdin,NULL);
    getchar();
	printf("Please input you want init name :\n			");
	setbuf(stdin,NULL);
	getchar();
	gets(data_admin.username);
    
	while(1){
    	i=0;
		printf("\nPlease input you want passsword :\n			");
		setbuf(stdin,NULL);
		while((ch=getch())!='\r'){
			if(i<20){
				pwd[i++]=ch;
				putchar('*');
			}
			else if(i>0&&ch=='\b'){
				--i;
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
			pwd[i]='\0';
		}
		i=0;
		printf("\nPlease input your passsword again:\n			");
		setbuf(stdin,NULL);
		while((ch=getch())!='\r'){
			if(i<20){
				pwd1[i++]=ch;
				putchar('*');
			}
			else if(i>0&&ch=='\b'){
				--i;
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
			pwd1[i]='\0';
		}
		if(strcmp(pwd,pwd1)){
			system("cls");
			printf("\nThe passward you input is different!");
		}
		else{
			break;
		}
	}
	
	system("cls");	
	for(i=0;i<20;i++)
	{
		data_admin.password[i] = pwd[i];
	}

	setbuf(stdin,NULL);
	printf("\n[0]anonymous   |   [1]Conductor   |   [2]manager   |   [9]admin\n");
	printf("	please input you want type\n(if you are admin)plseae input [9]:");
	setbuf(stdin,NULL);
	scanf("%d",&data_admin.type);
	getchar();

	printf("please input your phone number(only you know!!!):\n			");
	scanf("%s",data_admin.phone);
	getchar();

	setbuf(stdin,NULL);
	Account_Srv_Add(&data_admin);
}
//验证登录账号是否已存在，存在，保存登录用户信息到全局变量gl_CurUser，return 1；否则return 0
int Account_Srv_Verify(char usrName[],unsigned char pwd[])
{
	account_t usr;
    
    if(Account_Perst_SelByName(usrName,&usr)){
    	int a = 1;
    	if(strcmp(pwd,usr.password)){
			a = 0;
		}
	
		if(a){
			gl_CurUser = usr;
			return 1;
		}
		else{
			return 0;
		}
	}
	return 0;
}
int Account_Srv_Verifyno(char usrName[])
{
	account_t usr;
    if(Account_Perst_SelByName(usrName,&usr)){
    	gl_CurUser = usr;
    	return 1;
	}
	else{
		return 0;
	}
	return 0;
}

//根据用户名获取系统用户指针
account_node_t * Account_Srv_FindByUsrName(account_list_t list,char usrName[])
{
	account_list_t temp = list;
    while(list->next!=temp){
    	list = list->next;
    	if(!(strcmp(usrName,list->data.username))){
    		return list;
		}
	}
	return NULL;
}

//通过ID查询用户信息
int Account_Srv_FetchByID(int usrID, account_t *buf)
{
	return Account_Perst_SelectByID(usrID, buf);	
}
//通过用户名查询用户信息
int Account_Srv_FetchByName(char usrName[], account_t *buf)
{
	return Account_Perst_SelByName(usrName, buf);
}
//通过插入函数Insert创建新用户账号
int Account_Srv_Add(const account_t *data)
{
    return Account_Perst_Insert(data);
}
//通过更新函数Update修改系统用户
int Account_Srv_Modify(const account_t *data)
{
	return Account_Perst_Update(data);
}
//根据ID删除用户信息
int Account_Srv_DeleteByID(int usrID)
{
	return Account_Perst_DeleteByID(usrID);
}

//获取所有系统用户
int Account_Srv_FetchAll(account_list_t list)
{
    return Account_Perst_SelectAll(list);
}

