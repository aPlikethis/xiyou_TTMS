#ifndef ACCOUNTPERSIST_H_
#define ACCOUNTPERSIST_H_

#include "../Service/Account.h"

int Account_Perst_CheckAccFile();//检查文件是否能打开

int Account_Perst_SelByName(char usrName[], account_t *buf);//通过用户名登录
int Account_Perst_Insert(account_t *data);//插入
int Account_Perst_Update(const account_t *data);//更新用户
int Account_Perst_DeleteByID(int id);//通过ID删除
int Account_Perst_SelectByID(int id, account_t *buf);//通过ID查找
int Account_Perst_SelectAll(account_list_t list);//查询所有用户信息

#endif /* ACCOUNTPERSIST_H_ */