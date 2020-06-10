//系统用户登录界面
int SysLogin()
{
	system("clear");
    char ID[20];
	char Pwd[20];
	printf("\n    ======================================================================");
	printf("\n    ****************************Login  Systerm****************************");
	printf("\n    ======================================================================\n\n\n");
	Account_Srv_InitSys();
	printf("			User  ID: ");
	scanf("%s",ID);
	getchar();
	printf("			Passward: ");
	scanf("%s",Pwd);
}
//系统用户管理界面
int Account_UI_MgtEntry()
{
	char c;
	printf("\n    ======================================================================");
	printf("\n    ****************************Login  Systerm****************************");
	printf("\n    ======================================================================\n");
	printf("\n			1.Find User(A)\n");
	printf("\n			2.Add User(B)\n");
	printf("\n			3.Modify User(C)\n");
	printf("\n			4.Delete User(D)\n");
	printf("\n			5.Logdown(E)\n");
	printf("\n		Please choose an action: ");
	scanf("%c",&c);
	//switch(c){
	//	case 'A':---;  break;
	//	case 'B':---;  break;
	//	case 'C':---;  break;
	//	case 'D':---;  break;
	//	case 'E':---;  break;
	//}
}
//查询系统用户界面
int Account_UI_Find()
{
	char ID[20];
	printf("\n    ======================================================================");
	printf("\n    ****************************Find  Systerm****************************");
	printf("\n    ======================================================================\n");
	printf("\n         Please enter the user ID to find: ");
	scanf("%s",ID);
}
//创建系统新用户界面
int Account_UI_Add()
{
	char ID[20],Pwd[20];
	printf("\n    ======================================================================");
	printf("\n    ****************************Add  Systerm****************************");
	printf("\n    ======================================================================\n");
	printf("\n         Please enter the new user ID: ");
	scanf("%s",ID);
	printf("\n                The new user Passward: ");
	scanf("%s",Pwd);
}
//修改系统用户界面
int Account_UI_Mod()
{
	char c;
	printf("\n    ======================================================================");
	printf("\n    ****************************Modify  Systerm***************************");
	printf("\n    ======================================================================\n");
	printf("\n                 		1.Passward(A)");
	printf("\n                 		2.X(B)");
	printf("\n                 		3.Y(C)");
	printf("\n                 		4.Back(D)");
	printf("\n		  Choose an content to modify: ");
	scanf("%c",&c);
	//switch(c){
	//	case 'A':---;  break;
	//	case 'B':---;  break;
	//	case 'C':---;  break;
	//	case 'D':---;  break;
	//}
}
//删除系统用户信息界面
int Account_UI_Del()
{
	char ID[20];
	printf("\n    ======================================================================");
	printf("\n    ***************************Delete  Systerm****************************");
	printf("\n    ======================================================================\n");
	printf("\n           Please enter the user ID to delete: ");
	scanf("%s",ID);
}