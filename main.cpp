#define _CRT_SECURE_NO_WARNINGS 1
#include"Bank.h"
void menu1()
{
	cout << "1���빦��   " << "2 ע�Ṧ��" << endl;
	cout << "3.�˳�����" << endl;
}
void menu2()//����ɹ���Ĺ���
{
	cout << "1.���  " << "2.ȡ��   " << endl;
	cout << "3.��ѯ���" << "4.�û����ת��" << endl;
	cout << "5.��ѯ���׼�¼" << "6.�����˳�" << endl;
}
void Signup(int _id)
{
	Bank bank;
	int input;
	Init(&bank);//���ݼ���
	do {
		menu2();
		cout << "ѡ����" << endl;
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
			save(&bank, _id);//�˳�����
			break;
		}
	} while (input != 6);
	return;
}
void Load()
{

	int id;
	int passport;
	cout << "������Ҫ������˻�id:" << endl;
	int _id;
	cin >> _id;
	cout << "������Ҫ������˻�password:" << endl;
	int _passport;
	cin >> _passport;
	FILE* fp = fopen("C:\\�������\\customer.txt", "r");
	while (fscanf(fp, "%d %d", &id, &passport) != EOF)//
	{
		if (_id == id && _passport == passport)
		{
			Signup(_id);
			return;
		}

	}
	cout << "������󷵻ز˵���������" << endl;
}
int main(void)
{

	int a = 0;
	do {
		menu1();
		cout << "ѡ����" << endl;
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