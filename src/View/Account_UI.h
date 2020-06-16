#ifndef ACCOUNT_UI_H_
#define ACCOUNT_UI_H_
#include "../Service/Account.h"

static const int Account_PAGE_SIZE = 5;


//��ʶ����TTMS_SCU_Login
//ϵͳ�û���¼����
int SysLogin();

//��ʶ����TTMS_SCU_Account_UI_MgtEnt  
//ϵͳ�û�������� 
void Account_UI_MgtEntry();

//��ʶ����TTMS_SCU_Account_UI_Add 
//������ϵͳ�û�����
int Account_UI_Add(account_list_t list);

//��ʶ����TTMS_SCU_Account_UI_Mod
//�޸�ϵͳ�û�����
int Account_UI_Modify(char usrName[]);

//��ʶ����TTMS_SCU_Account_UI_Del
//ɾ��ϵͳ�û����� 
int Account_UI_Delete(account_list_t list,char usrName[]);

//��ʶ����TTMS_SCU_Account-UI_Que
//��ѯϵͳ�û�����
int Account_UI_Query(account_list_t list,char usrName[]);

#endif /* ACCOUNT_UI_H_ */
