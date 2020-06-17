
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../Common/list.h"
#include "MaiAccount_UI.h" 
#include "Account_UI.h"
#include "../Persistence/Account_Persist.h"

//系统用户登录界面
int SysLogin()
{
    system("cls");
	printf(
	    "================================================================================\n"
		"   *************  ************ *****     *****        ********      *** \n"
		"   *************  ************ ******   ******      *******         *** \n"
		"        ***           ***      ***  ** **  ***    *****             *** \n"
		"        ***           ***      ***   ***   ***      ******          *** \n"
		"        ***           ***      ***         ***        ******        *** \n"
		"        ***           ***      ***         ***          *****           \n"
		"        ***           ***      ***         ***       ******        *****\n"
		"        ***           ***      ***         ***    ********         *****\n"
		"                                                                        \n"
		"        ##             ## ####### ##       ######    ###    ####   #### ####### \n"
		"        ##     ###     ## ##      ##      ##       ##   ##  ## ## ## ## ##      \n"
		"         ##   ## ##   ##  ####### ##     ##       ##     ## ##  ###  ## ####### \n"
		"          ## ##   ## ##   ##      ##      ##       ##   ##  ##       ## ##      \n"
		"           ###     ###    ####### #######  ######    ###    ##       ## ####### \n"
		"================================================================================\n");
	printf("please input [Enter] to continue!");
	getchar();
    if(Account_Perst_CheckAccFile()==0)
	    Account_Srv_InitSys();

	int x = 3,i;
	char ch;
	while(x>0){
		i = 0;
		printf("You have %d login opportunities\n",x);
		char usrName[20],pwd[20];
		printf("Please input your name:");
		setbuf(stdin,NULL);
		scanf("%s",usrName);		
		printf("\nPlease input your passsword:");
		setbuf(stdin,NULL);
		scanf("%s", pwd);
		getchar();
//		while((ch=getch())!='\r'){
//			if(i<20){
//				pwd[i++]=ch;
//				putchar('*');
//			}
//			else if(i>0&&ch=='\b'){
//				--i;
//				putchar('\b');
//				putchar(' ');
//				putchar('\b');
//			}
//			pwd[i]='\0';
//		}

		if(Account_Srv_Verify(usrName,pwd)){

			account_t data;
			int i = 0;
            Account_Srv_FetchByName(usrName, &data);
            gl_CurUser.id = data.id;
            while (usrName[i] != '\0') {
                gl_CurUser.username[i] = usrName[i];
                gl_CurUser.password[i] = pwd[i];
                i++;
            }
            gl_CurUser.type = data.type;
            gl_CurUser.phone = data.phone;

            printf("\nWelcome distinguished users,please input [Enter]!\n");
            getchar();
			return 1;
		}
		else{
			printf("\nlogin in error\n");
			x--;
		}
	}

	if(x==0){
		char c;
		printf("Do you forget your password and want to reset it?\n[Y]ES	or	[N]o: ");
		getchar();
		scanf("%c",&c);
		if(c=='Y'||c=='y'){
			MaiAccount_UI_Mgt();
		}
	}
	return 0;
}

//身份判别
char Account_UI_Status2Char(account_type_t status)
{
	if (status == 0)
		return 'N';
	else if (status == 1)
		return 'X';
	else if (status == 9)
		return 'A';
	else if (status == 2)
		return 'M';
}

//系统用户管理界面
void Account_UI_MgtEntry(void)
{
    printf("%d", gl_CurUser.type);
	if(gl_CurUser.type!=USR_ADMIN){
		printf("you isn't admin!please input [Enter]");
		getchar();
		return ;
	}
	
	int x,id;
	char ch,usrName[20];
	account_list_t head;
	account_node_t *p;
	Pagination_t paging;
	
	List_Init(head,account_node_t);
	paging.offset = 0;
	paging.pageSize = Account_PAGE_SIZE;
	
	paging.totalRecords = Account_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head,paging);
	
	do{

	    system("cls");
        printf("user: %s | id: %d \n", gl_CurUser.username, gl_CurUser.id);
		printf("\n[N]匿名用户    |    [X]售票员     |     [M]经理     |     [A]系统管理员");
		printf("\n==============================================================================\n");
		printf("*************************Account Management Systerm****************************\n");
		printf("	%3s %18s %23s %16s\n","ID","username","password","type");	
		printf("-------------------------------------------------------------------------------\n");
		
		Paging_ViewPage_ForEach(head,paging,account_node_t,p,x) {
			printf("%3d %18s ",p->data.id,p->data.username);
			printf(p->data.password);
			printf(" %6c\n",Account_UI_Status2Char(p->data.type));
		}
		printf("-------Total Records:%2d-------------------Page%2d/%2d----\n",
				paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
		printf("*******************************************************************************\n");
		printf("[p]revPage | [N]extPage | [A]dd | [D]elete | [Q]uery | [M]od | [R]etuen");
		printf("\n==============================================================================\n");
		printf("Please input your Choice: ");
		setbuf(stdin,NULL);
		scanf("%c",&ch);
		getchar();
		switch(ch){
			case 'a':
			case 'A':system("cls");
					if(Account_UI_Add(head)){
						paging.totalRecords = Account_Srv_FetchAll(head);
					}
					else{
						printf("This user is exist!\n");
					}
					break;
			case 'd':
			case 'D':system("cls");
					printf("Input the username:");
					setbuf(stdin,NULL);
					scanf("%s",usrName);
					getchar();
					if(Account_UI_Delete(head,usrName)){
						printf("delete accept\n");
						paging.totalRecords = Account_Srv_FetchAll(head);
						List_Paging(head,paging,account_node_t);
					}
					else{
						printf("Delete Error!\n");
					}
					break;
			case 'q':
			case 'Q':system("cls");
					printf("Input the username:");
					setbuf(stdin,NULL);
					scanf("%s",usrName);
					getchar();
					if(Account_UI_Query(head,usrName)){
						paging.totalRecords = Account_Srv_FetchAll(head);
						List_Paging(head, paging, account_node_t);
					}
					else{
						printf("Query Error\n");
					}
					break;
			case 'm':
			case 'M':system("cls");
					
					if(Account_UI_Modify(gl_CurUser.username)){
						printf("Mod accept\n");
						paging.totalRecords = Account_Srv_FetchAll(head);
						List_Paging(head, paging, account_node_t);
					}
					break;
			case 'p':
			case 'P':system("cls");
					if(Pageing_IsLastPage(paging)){
						Paging_Locate_OffsetPage(head,paging,-1,account_node_t);
					}
					break;
			case 'n':
			case 'N':system("cls");
					if(!Pageing_IsLastPage(paging)){
						Paging_Locate_OffsetPage(head,paging,1,account_node_t);
					}
					break;
		}
	}while(ch!='r'&&ch!='R');
	List_Destroy(head,account_node_t); 
}

//创建系统新用户界面
int Account_UI_Add(account_list_t list)
{
	account_t data;
	int newCount = 0;
	char c;
	do
	{
        system("cls");
        printf("user: %s | id: %d \n", gl_CurUser.username, gl_CurUser.id);
		printf("\n==============================================================================\n");
		printf("*****************************Account Add Systerm*******************************\n");	
		printf("-------------------------------------------------------------------------------");
		printf("\nplease input the new username you add:");
		setbuf(stdin,NULL);
		scanf("%s",data.username);
		getchar();
		printf("\n==============================================================================\n");
		account_list_t temp = Account_Srv_FindByUsrName(list,data.username);
		if(temp!=NULL){
			printf("this user is exist\n");
			printf("[A]dd another,[R]eturn:");
			setbuf(stdin,NULL);
			scanf("%c",&c);
			getchar();
		}
		else{
			printf("please input the password:");
			setbuf(stdin,NULL);
			char pwd[20];
			scanf("%s", data.password);
//			while((ch=getch())!='\r'){
//				int i;
//				if(i<20){
//					pwd[i++]=ch;
//					putchar('*');
//				}
//				else if(i>0&&ch=='\b'){
//					--i;
//					putchar('\b');
//					putchar(' ');
//					putchar('\b');
//				}
//				pwd[i]='\0';
//			}
		}
		printf("Please input the type:\n");
		printf("==============================================================================\n");
		printf("[0]Anonymous user | [1]conductor | [2]manager | [9]system administrator:");
		setbuf(stdin,NULL);
		scanf("%d",&data.type);
		getchar();
		printf("Please input your phone number(only you know!!!):\n");
		scanf("%d",&data.phone);
		getchar();
		
		if(Account_Srv_Add(&data)){
			newCount ++;
			Account_Srv_FetchAll(list);
			printf("Add Successfully!\n"); 
		}
		else{
			printf("Add Failed!\n");
		} 
		printf("-------------------------------------------------------------------------------");
		printf("[A]dd more,[R]etuen:");
		setbuf(stdin,NULL);
		scanf("%c",&c);
		char ch;
		while((ch = getchar())!='\n'&&ch!=EOF);
	
	}while('a'==c||'A'==c);
	return newCount;
}

//修改系统用户界面
int Account_UI_Modify(char usrName[])
{
    account_t data;
	int found = Account_Srv_FetchByID(gl_CurUser.id, &data);
	if(found == 0) {
        return found;
	}
		int m = 10;
		do
		{
		    char pwd[20],ch;
		    printf("please input the old password:");
            scanf("%s", pwd);
		    if(Account_Srv_Verify(gl_CurUser.username, pwd)) {
                printf("please input the new password:");
                setbuf(stdin, NULL);
                scanf("%s", pwd);
//			while((ch=getch())!='\r'){
//				int i;
//				if(i<20){
//					pwd[i++]=ch;
//					putchar('*');
//				}
//				else if(i>0&&ch=='\b'){
//					--i;
//					putchar('\b');
//					putchar(' ');
//					putchar('\b');
//				}
//				pwd[i]='\0';
//			}
                int x = 1;
                if (strcmp(pwd, data.password)) {
                    x = 0;
                }
                if (x) {
                    printf("Mod error!The same password!please choice:\n");
                    printf(" [0]exit  |  [1]try again\n");
                    scanf("%d", &m);
                    setbuf(stdin, NULL);
                } else {
                    int i;
                    for (i = 0; i < 20; i++) {
                        data.password[i] = pwd[i];
                    }
                    int a = Account_Srv_Modify(&data);
                    if (a == 0) {
                        return 0;
                    }
//				Account_Srv_FetchAll(list);
                    return 1;
                }
            }
		    else {
		        printf("password error, please re-enter:");
		    }
		}while(m!=0);

}

//删除系统用户信息界面
int Account_UI_Delete(account_list_t list,char usrName[])
{
	account_list_t temp = Account_Srv_FindByUsrName(list,usrName);
	if(temp!=NULL){
		Account_Srv_DeleteByID(temp->data.id);
		Account_Srv_FetchAll(list);
		return 1;
	}
	return 0;
}

//查询系统用户界面
int Account_UI_Query(account_list_t list, char usrName[])
{
	account_list_t temp = Account_Srv_FindByUsrName(list,usrName);
	if(temp!=NULL){
		printf("user ID:%d\n",temp->data.id);
		printf("user passwore:%s\n",temp->data.password);
		putchar('\n');
		printf("user name:%s\n",temp->data.username);
		printf("user type:%c\n",Account_UI_Status2Char(temp->data.type));
		return 1;
	}
	return 0;
}
