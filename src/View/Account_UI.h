#ifndef ACCOUNT_UI_H_
#define ACCOUNT_UI_H_
#include "../Service/Account.h"

static const int Account_PAGE_SIZE = 5;


//标识符：TTMS_SCU_Login
//系统用户登录界面
int SysLogin();

//标识符：TTMS_SCU_Account_UI_MgtEnt  
//系统用户管理界面 
void Account_UI_MgtEntry();

//标识符：TTMS_SCU_Account_UI_Add 
//创建新系统用户界面
int Account_UI_Add(account_list_t list);

//标识符：TTMS_SCU_Account_UI_Mod
//修改系统用户界面
int Account_UI_Modify(char usrName[]);

//标识符：TTMS_SCU_Account_UI_Del
//删除系统用户界面 
int Account_UI_Delete(account_list_t list,char usrName[]);

//标识符：TTMS_SCU_Account-UI_Que
//查询系统用户界面
int Account_UI_Query(account_list_t list,char usrName[]);

#endif /* ACCOUNT_UI_H_ */
