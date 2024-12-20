#define _CRT_SECURE_NO_WARNINGS 1
#include"Bank.h"
int get_pos(int id, Bank* bank)
{
	for (int x = 0; x < bank->customer.size(); ++x)
	{
		if (bank->customer[x].id == id) return x;
	}
	return -1;
}
void modify(Bank* bank, double money, string record, int pos)
{
	bank->customer[pos].all_money = money;
	bank->customer[pos].trade_record = record;
}
int Is_same(int _id)//�ж�id�Ƿ�Ψһ
{
	int id;
	int passport;
	FILE* fp = fopen("C:\\�������\\customer.txt", "r");
	while (fscanf(fp, "%d %d", &id, &passport) != EOF)
	{
		if (id == _id)return 1;
	}
	return 0;
}
void zhuce()
{
	cout << "������ע��id:" << endl;
	int id;
	cin >> id;
	cout << "����������(������6λ������):" << endl;
	int passport;
	cin >> passport;
	while (Is_same(id))
	{
		cout << "����������ע��id,��id�Ѿ���ʹ��:" << endl;
		cin >> id;
	}
	//��¼�û�����,,id
	FILE* fp = fopen("C:\\�������\\customer.txt", "a");
	if (!fp)perror("fopen");
	fprintf(fp, "%d  %d\n", id, passport);
	fclose(fp);


	string strr = "C:\\�������\\�û�����\\" + to_string(id) + "�û����׼�¼.txt";
	const char* str = strr.data();
	FILE* fppp = fopen(str, "a");
	fclose(fppp);
	fppp = nullptr;
}
Customer push(int _id, double _all_money, string str)
{

	Customer customer;
	customer.id = _id;
	customer.all_money += _all_money;
	customer.trade_record = str;
	return customer;
}
void Init(Bank* bank)//���ݵ���
{

	string str = "C:\\�������\\�û���Ϣ\\�û���Ϣ.txt";
	const char* strs = str.data();
	FILE* fpp = fopen(strs, "r");
	int _id; int passport;

	FILE* fp = fopen("C:\\�������\\customer.txt", "r");
	if (!fp)perror("fopen");
	int x = 0;
	while (fscanf(fp, "%d  %d\n", &_id, &passport) != EOF)
	{
		double money = 0;
		string record;
		string add;
		fscanf(fpp, "%d  %lf", &_id, &money);//�����û���Ϣ,��Ҫ�Ƕ�Ǯ������
		string strr = "C:\\�������\\�û�����\\" + to_string(_id) + "�û����׼�¼.txt";
		const char* strs = strr.data();
		ifstream fppp(strs);
		while (getline(fppp, record)) {
			add += record;
			add += "      ,";
		}
		Customer customer = push(_id, money, add);
		bank->customer.push_back(customer);
		fppp.close();
		int pos = get_pos(_id, bank);
		bank->customer[pos].all_money = money;//����Ǯ
	}
	fclose(fpp);
}
void deposit(Bank* bank, int id)
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	char* str = ctime(&now_time);
	string time = str;//ʱ��
	cout << "������Ҫ�����Ǯ:" << endl;
	double money;
	cin >> money;
	string strrs = to_string(money);
	string record = time + "���" + strrs + '\n';
	//�޸�����
	int pos = get_pos(id, bank);
	bank->customer[pos].all_money += money;
	bank->customer[pos].trade_record = record;
	string strr = "C:\\�������\\�û�����\\" + to_string(id) + "�û����׼�¼.txt";
	const char* road = strr.data();
	FILE* fp = fopen(road, "a");
	fprintf(fp, "%s", &record[0]);
	fclose(fp);

}
void withdraw(Bank* bank, int id)
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	char* str = ctime(&now_time);
	string time = str;//ʱ��
	int pos = get_pos(id, bank);
	double money = bank->customer[pos].all_money;
	cout << "�������Ϊ" << money << endl;
	cout << "Ҫȡ������Ǯ" << endl;
	double _money;
	cin >> _money;
	while (money - _money < 0)
	{
		cout << "������������" << endl;
		cin >> _money;
	}
	money -= _money;
	string strs = to_string(money);
	string record = time + "ȡ��" + strs + '\n';
	//�޸�����
	modify(bank, money, record, pos);
	string strr = "C:\\�������\\�û�����\\" + to_string(id) + "�û����׼�¼.txt";
	const char* road = strr.data();
	FILE* fp = fopen(road, "a");
	fprintf(fp, "%s", &record[0]);
	fclose(fp);
}
void show_money(Bank* bank, int id)
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	char* str = ctime(&now_time);
	string time = str;//ʱ��
	int pos = get_pos(id, bank);
	double money = bank->customer[pos].all_money;
	cout << "�������Ϊ" << money << endl;
	string strs = to_string(money);
	string record = time + "��Ѱ���" + strs + '\n';
	string strr = "C:\\�������\\�û�����\\" + to_string(id) + "�û����׼�¼.txt";
	const char* road = strr.data();
	FILE* fp = fopen(road, "a");
	fprintf(fp, "%s", &record[0]);
	fclose(fp);
}
void change_money(Bank* bank, int id)
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	char* str = ctime(&now_time);
	string time = str;//ʱ��
	cout << "��������Ҫת�˵�id:" << endl;
	int _id;
	cin >> _id;
	int pos = get_pos(_id, bank);
	while (pos == -1 && id != _id)
	{
		cout << "���û�������,����������߲��ܸ��Լ�ת��,����������id" << endl;
		cin >> _id;
		pos = get_pos(_id, bank);
	}
	int _pos = get_pos(id, bank);
	double money = bank->customer[_pos].all_money;
	cout << "�������Ϊ" << money << endl;
	cout << "Ҫת������Ǯ" << endl;
	double _money;
	cin >> _money;
	while (money - _money < 0)
	{
		cout << "������������" << endl;
		cin >> _money;
	}
	money -= _money;

	string num = to_string(_money);//ת��Ǯ
	string people = to_string(_id);
	string record = time + "ת��" + num + "��" + people;

	//�޸�����
	bank->customer[_pos].all_money -= _money;
	bank->customer[pos].all_money += _money;
	string strr = "C:\\�������\\�û�����\\" + to_string(id) + "�û����׼�¼.txt";
	const char* road = strr.data();
	FILE* fp = fopen(road, "a");
	fprintf(fp, "%s", &record[0]);
	fclose(fp);
}
void show_trade(Bank* bank, int id)
{
	string add;
	string record;

	cout << "����Ϊ�û�" << id << "�Ľ��׼�¼" << endl;
	string strr = "C:\\�������\\�û�����\\" + to_string(id) + "�û����׼�¼.txt";
	ifstream fppp(strr);
	while (getline(fppp, record)) {
		add += record;
		add += "      \n";
	}
	cout << add << endl << endl;
	fppp.close();
}
void save(Bank* bank, int id)//�������
{
	int pos = get_pos(id, bank);
	string str = "C:\\�������\\�û���Ϣ\\�û���Ϣ.txt";
	const char* Road = str.data();
	FILE* fp = fopen(Road, "w");
	for (int x = 0; x < bank->customer.size(); ++x)
	{
		fprintf(fp, "%d    %lf\n", bank->customer[x].id, bank->customer[x].all_money);
	}
	fclose(fp);
	return;
}