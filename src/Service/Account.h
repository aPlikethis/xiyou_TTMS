#ifndef ACCOUNTPERSIST_H_
#define ACCOUNTPERSIST_H_

#include "../Service/Account.h"

int Account_Srv_InitSyS();
int Account_Srv_Verify(char usrName[],char pwd[]);
int Account_Srv_FindUSer();
int Account_Srv_Add();
int Account_Srv_Modify(const account_t *date);
int Account_Srv_DeleteByID();
int Account_Srv_FindByUsrName();

#endif /* ACCOUNTPERSIST_H_ */