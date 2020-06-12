#ifndef ACCOUNTPERSIST_H_
#define ACCOUNTPERSIST_H_

#include "../Service/Account.h"

//定义枚举类型account_type_t，描述用户的角色
typedef enum {
	USR_ANOMY = 0, //USR_ANOMY  匿名用户（初始化账号，目的是创建其他账号，权限等同于系统管理员）
	USR_CLERK = 1, //USR_CLERK  售票员（查询演出、查询演出票、售票、退票以及统计销售额）
	USR_MANGE = 2, //USR_MANGE  剧院经理（管理剧目、安排演出、查询演出、查询巡演出票、统计销售额、统计票房）
	USR_ADMIN = 9，//USR_ADMIN  系统管理员（管理演出厅、管理系统用户、设置作为）
} account_type_t;

//定义系统用户账号数据类型，描述用户账号信息
typedef struct {
	int  id;//用户id
	account_type_t type;//用户类型
	char username[20];//用户名
	unsigned char password[20];//用户密码
	char phone[15];//手机号
} account_t;

//定义系统用户账号双向链表
typedef struct account_node {
	account_t data;//实体数据
	struct account_node *next, *prev;//前向指针prev，后向指针next
} account_node_t, *account_list_t;

account_t gl_CurUser;

//标识符：TTMS_SCU_Account_Srv_Verify
//创建管理员Admin匿名系统用户
void Account_Srv_InitSys();

//标识符：TTMS_SCU_Account_Srv_Verify
//功能：验证系统用户的用户名和密码
int Account_Srv_Verify(char usrName[],unsigned char pwd[]);
int Account_Srv_Verifyno(char usrName[]);

//标识符：TTMS_SCU_Account_Srv_Verify
//功能：添加新系统用户
int Account_Srv_Add(const account_t *data);

//标识符：TTMS_SCU_Account_Srv_Verify
//功能：修改系统用户
int Account_Srv_Modify(const account_t *data);

//标识符：TTMS_SCU_Account_Srv_Verify
//功能：根据ID删除系统用户
int Account_Srv_DeleteByID(int usrID);

//标识符：TTMS_SCU_Account_Srv_Verify
//功能：根据ID获取系统用户
int Account_Srv_FetchByID(int usrID, account_t *buf);
//标识符：TTMS_SCU_Account_Srv_Verify
//功能：根据用户名获取系统用户
int Account_Srv_FetchByName(char usrName[], account_t *buf);

//标识符：TTMS_SCU_Account_Srv_Verify
//获取所有系统用户
int Account_Srv_FetchAll(account_list_t list);

//标识符：TTMS_SCU_Account_Srv_Verify
//根据用户名获取系统用户指针
account_node_t *Account_Srv_FindByUsrName(account_list_t list,char usrName[]);

#endif //ACCOUNT_H_
_
