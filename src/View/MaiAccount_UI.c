#include "MaiAccount_UI.h"
#include "../Common/list.h"
#include "../Service/Account.h"
#include <string.h>
#include <stdio.h>


//维护个人资料管理入口界面
void MaiAccount_UI_MgtEntry ()
{
    char ch;
	system("cls");
	account_t data = gl_CurUser;
	char pwd[20],pwd1[20];
	int t = 3,i;
	while(t--){
		if(t==0){
			break;
		}
    	i=0;
		printf("\nPlease input your old passsword :\n			");
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
		int x = 1;
		if(strcmp(pwd,data.password)!=0)
            x = 0;

        if(x){
			system("cls");
        	printf("\naccept!!");
        	int j=4;
        	while(j--){
        		if(j==0){
        			break;
				}
        		printf("\nyou have %d times\n",j);
        		printf("\nPlease input your new passsword :\n			");
				setbuf(stdin,NULL);
				i=0;
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
				int x1 = 1;
        		if(strcmp(pwd,data.password)!=0){
        			x1=0;
				}

        		if(x1){
					system("cls");
        			printf("\nthe password is same as old one,please input again!!");
				}
				else{
					system("cls");
					printf("\nplease input the new password again:\n			");
					setbuf(stdin,NULL);
					i=0;
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
					int x2 = 1;
        			if(strcmp(pwd,pwd1)!=0){
        				x2=0;
					}

        			if(x2){
        				for(i=0;i<20;i++){
        					data.password[i] = pwd[i];
						}
						Account_Srv_Modify(&data);
						return ;
					}
					else{
						system("cls");
						printf("\nthe  two new passwords you input is different!\nPlease try again.\n");
					 }
                }
            }
            return ;
        }
    }
    return ;
}
void MaiAccount_UI_Mgt ()
{
    system("cls");
	account_t data;
	char name[20],phone[15];
	int i = 0;
	char ch;
	
	while(1){
		printf("please input your name:");
		scanf("%s",name);
		getchar();
		if(Account_Srv_Verifyno(name)){
			data = gl_CurUser;
			break;
		}
		else{
			char c;
			printf("Without this user,please [R]einput or [E]xit\n");
			scanf("%c",&c);
			getchar();
			if(c=='E'||c=='e'){
				return;
			}
			else{
				continue;
			}
		}
	}
	
	printf("Please input your phone number.\n");
	int t = 3;
	while(t--){
		printf("you have %d times\n",t);
		scanf("%s",phone);
		getchar();
		if(strcmp(phone,data.phone)!=0){
			printf("phone number Error!\n");
		}
		else{
			break;
		}
	}
	if(t<=0){
		return;
	}
	
	char pwd[20],pwd1[20];
	while(1){
    	i=0;
		printf("\nPlease input your new passsword :\n			");
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
	
	for(i = 0;i < 20;i++){
        data.password[i] = pwd[i];
    }
    Account_Srv_Modify(&data);
    printf("modify accept,please input [E]nter\n");
    getchar();
}
