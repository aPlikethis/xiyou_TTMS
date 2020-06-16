#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <stdio.h>

//����ö������account_type_t�������û��Ľ�ɫ
typedef enum {
	USR_ANOMY = 0, //USR_ANOMY  �����û�����ʼ���˺ţ�Ŀ���Ǵ��������˺ţ�Ȩ�޵�ͬ��ϵͳ����Ա��
	USR_CLERK = 1, //USR_CLERK  ��ƱԱ����ѯ�ݳ�����ѯ�ݳ�Ʊ����Ʊ����Ʊ�Լ�ͳ�����۶
	USR_MANGE = 2, //USR_MANGE  ��Ժ���������Ŀ�������ݳ�����ѯ�ݳ�����ѯѲ�ݳ�Ʊ��ͳ�����۶ͳ��Ʊ����
	USR_ADMIN = 9, //USR_ADMIN  ϵͳ����Ա�������ݳ���������ϵͳ�û���������Ϊ��
}account_type_t;

//����ϵͳ�û��˺��������ͣ������û��˺���Ϣ
typedef struct {
	int  id;//�û�id
	account_type_t type;//�û�����
	char username[20];//�û���
	char password[20];//�û�����
	int  phone;//�ֻ���
} account_t;

//����ϵͳ�û��˺�˫������
typedef struct account_node {
	account_t data;//ʵ������
	struct account_node *next, *prev;//ǰ��ָ��prev������ָ��next
} account_node_t, *account_list_t;

account_t gl_CurUser;

//��ʶ����TTMS_SCU_Account_Srv_InitSys
//��������ԱAdmin����ϵͳ�û�
void Account_Srv_InitSys();

//��ʶ����TTMS_SCU_Account_Srv_Verify
//���ܣ���֤ϵͳ�û����û���������
int Account_Srv_Verify(char usrName[],char pwd[]);
int Account_Srv_Verifyno(char usrName[]);

//��ʶ����TTMS_SCU_Account_Srv_Add
//���ܣ������ϵͳ�û�
int Account_Srv_Add(account_t *data);

//��ʶ����TTMS_SCU_Account_Srv_Mod
//���ܣ��޸�ϵͳ�û�
int Account_Srv_Modify(account_t *data);

//��ʶ����TTMS_SCU_Account_Srv_Del
//���ܣ�����IDɾ��ϵͳ�û�
int Account_Srv_DeleteByID(int usrID);

//��ʶ����TTMS_SCU_Account_Srv_FetchByID
//���ܣ�����ID��ȡϵͳ�û�
int Account_Srv_FetchByID(int usrID, account_t *buf);
//��ʶ����TTMS_SCU_Account_Srv_FetchByName
//���ܣ������û�����ȡϵͳ�û�
int Account_Srv_FetchByName(char usrName[], account_t *buf);

//��ʶ����TTMS_SCU_Account_Srv_FetchAll
//��ȡ����ϵͳ�û�
int Account_Srv_FetchAll(account_list_t list);

//��ʶ����TTMS_SCU_Account_Srv_FindByUsrName
//�����û�����ȡϵͳ�û�ָ��
account_node_t *Account_Srv_FindByUsrName(account_list_t list,char usrName[]);

#endif //ACCOUNT_H_
