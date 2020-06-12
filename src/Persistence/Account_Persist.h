#ifndef ACCOUNTPERSIST_H_
#define ACCOUNTPERSIST_H_

#include "../Persistence/Account_Persist.h"

//检查文件是否能打开
int Account_Perst_CheckAccFile();

//通过用户名查找系统用户
int Account_Perst_SelByName(char usrName[], account_t *buf);
//通过ID查找系统用户
int Account_Perst_SelectByID(int id, account_t *buf);


//标识符：TTMS_SCU_Account_Perst_Insert
//存储新系统用户
int Account_Perst_Insert(account_t *data);

//标识符：TTMS_SCU_Account_Perst_Update
//更新系统用户
int Account_Perst_Update(const account_t *data);

//标识符：TTMS_SCU_Account_Perst_DeleteByID
//通过ID删除系统用户
int Account_Perst_DeleteByID(int id);

//标识符：TTMS_SCU_Account_Perst_SelAll
//载入所有用户信息
int Account_Perst_SelectAll(account_list_t list);

#endif /* ACCOUNTPERSIST_H_ */
