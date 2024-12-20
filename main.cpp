#define _CRT_SECURE_NO_WARNINGS 1
#include"Bank.h"
void menu1()
{
	cout << "1登入功能   " << "2 注册功能" << endl;
	cout << "3.退出功能" << endl;
}
void menu2()//登入成功后的功能
{
	cout << "1.存款  " << "2.取款   " << endl;
	cout << "3.查询余额" << "4.用户金额转账" << endl;
	cout << "5.查询交易记录" << "6.保存退出" << endl;
}
void Signup(int _id)
{
	Bank bank;
	int input;
	Init(&bank);//数据加载
	do {
		menu2();
		cout << "选择功能" << endl;
		cin >> input;
		switch (input)
		{
		case 1:
			deposit(&bank, _id);
			break;
		case 2:
			withdraw(&bank, _id);
			break;
		case 3:
			show_money(&bank, _id);
			break;
		case 4:
			change_money(&bank, _id);
			break;
		case 5:
			show_trade(&bank, _id);
			break;
		case 6:
			save(&bank, _id);//退出保存
			break;
		}
	} while (input != 6);
	return;
}
void Load()
{

	int id;
	int passport;
	cout << "请输入要登入的账户id:" << endl;
	int _id;
	cin >> _id;
	cout << "请输入要登入的账户password:" << endl;
	int _passport;
	cin >> _passport;
	FILE* fp = fopen("C:\\面向对象\\customer.txt", "r");
	while (fscanf(fp, "%d %d", &id, &passport) != EOF)//
	{
		if (_id == id && _passport == passport)
		{
			Signup(_id);
			return;
		}

	}
	cout << "输入错误返回菜单重新输入" << endl;
}
int main(void)
{

	int a = 0;
	do {
		menu1();
		cout << "选择功能" << endl;
		cin >> a;
		switch (a)
		{
		case 1:
			Load();
			break;
		case 2:
			zhuce();
			break;
		case 3:
			break;
		}
	} while (a != 3);


}