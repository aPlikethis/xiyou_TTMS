//系统用户登录界面
int SysLogin()
{
    char ID[20];
	char Pwd[20];
	printf("\n    ****************************Login  Systerm****************************\n\n\n");
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
	printf("\n    ****************************MgtEntry   Systerm****************************\n\n\n");
	printf("\n			1.Find User(A)\n");
	printf("\n			2.Add User(B)\n");
	printf("\n			3.Modify User(C)\n");
	printf("\n			4.Delete User(D)\n");
	printf("\n			5.Logdown(E)\n");
	printf("\n			Please choose an action: ");
	scanf("%c",&c);
}
//查询系统用户界面
int Account_UI_Find()
{}
//创建系统新用户界面
int Account_UI_Add()
{}
//修改系统用户界面
int Account_UI_Mod()
{}
//删除系统用户信息界面
int Account_UI_Del()
{}