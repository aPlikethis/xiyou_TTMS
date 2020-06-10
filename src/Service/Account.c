#include "Account.h"
#include "../Common/list.h"
#include "../Persistence/Account_Persist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

account_t gl_CurUser;
const int lenn;
//创建管理员Admin匿名系统用户
void Account_Srv_InitSyS()
{
	if(Account_Perst_CheckAccFile()==1){
		return ;
	}
}
//验证系统用户
int Account_Srv_Verify(char usrName[],unsigned char pwd[])
{}
//查询用户账号
int Account_Srv_FetchByID(int usrID, account_t *buf)
{}
int Account_Srv_FetchByName(char usrName[], account_t *buf)
{}
//创建新用户账号
int Account_Srv_Add(const account_t *data)
{}
//修改系统用户
int Account_Srv_Modify(const account_t *data)
{}
//根据ID删除用户信息
int Account_Srv_DeleteByID(int usrID)
{}
//根据用户名获取系统用户指针
int Account_Srv_FindByUsrName(char *name[])
{}

//获取所有系统用户
int Account_Srv_FetchAll(account_list_t list)
{}
//根据用户名获取系统用户指针
account_node_t * Account_Srv_FindByUsrName(account_list_t list,char usrName[])
{}
int Account_Srv_Verifyno(char usrName[])
{}