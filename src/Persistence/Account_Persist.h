#ifndef ACCOUNT_PERSIST_H_
#define ACCOUNT_PERSIST_H_

#include "../Service/Account.h"

//����ļ��Ƿ��ܴ�
int Account_Perst_CheckAccFile();

//ͨ���û�������ϵͳ�û�
int Account_Perst_SelByName(char usrName[], account_t *buf);
//ͨ��ID����ϵͳ�û�
int Account_Perst_SelectByID(int id, account_t *buf);


//��ʶ����TTMS_SCU_Account_Perst_Insert
//�洢��ϵͳ�û�
int Account_Perst_Insert(account_t *data);

//��ʶ����TTMS_SCU_Account_Perst_Update
//����ϵͳ�û�
int Account_Perst_Update(account_t *data);

//��ʶ����TTMS_SCU_Account_Perst_RemByID
//ͨ��IDɾ��ϵͳ�û�
int Account_Perst_RemByID(int id);

//��ʶ����TTMS_SCU_Account_Perst_SelAll
//���������û���Ϣ
int Account_Perst_SelectAll(account_list_t list);

#endif /* ACCOUNTPERSIST_H_ */
