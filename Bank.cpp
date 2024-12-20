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
int Is_same(int _id)//判断id是否唯一
{
	int id;
	int passport;
	FILE* fp = fopen("C:\\面向对象\\customer.txt", "r");
	while (fscanf(fp, "%d %d", &id, &passport) != EOF)
	{
		if (id == _id)return 1;
	}
	return 0;
}
void zhuce()
{
	cout << "请输入注册id:" << endl;
	int id;
	cin >> id;
	cout << "请输入密码(不大于6位的数字):" << endl;
	int passport;
	cin >> passport;
	while (Is_same(id))
	{
		cout << "请重新输入注册id,此id已经被使用:" << endl;
		cin >> id;
	}
	//记录用户密码,,id
	FILE* fp = fopen("C:\\面向对象\\customer.txt", "a");
	if (!fp)perror("fopen");
	fprintf(fp, "%d  %d\n", id, passport);
	fclose(fp);


	string strr = "C:\\面向对象\\用户交易\\" + to_string(id) + "用户交易记录.txt";
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
void Init(Bank* bank)//数据导入
{

	string str = "C:\\面向对象\\用户信息\\用户信息.txt";
	const char* strs = str.data();
	FILE* fpp = fopen(strs, "r");
	int _id; int passport;

	FILE* fp = fopen("C:\\面向对象\\customer.txt", "r");
	if (!fp)perror("fopen");
	int x = 0;
	while (fscanf(fp, "%d  %d\n", &_id, &passport) != EOF)
	{
		double money = 0;
		string record;
		string add;
		fscanf(fpp, "%d  %lf", &_id, &money);//载入用户信息,主要是对钱的载入
		string strr = "C:\\面向对象\\用户交易\\" + to_string(_id) + "用户交易记录.txt";
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
		bank->customer[pos].all_money = money;//导入钱
	}
	fclose(fpp);
}
void deposit(Bank* bank, int id)
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	char* str = ctime(&now_time);
	string time = str;//时间
	cout << "请输入要存多少钱:" << endl;
	double money;
	cin >> money;
	string strrs = to_string(money);
	string record = time + "存款" + strrs + '\n';
	//修改数据
	int pos = get_pos(id, bank);
	bank->customer[pos].all_money += money;
	bank->customer[pos].trade_record = record;
	string strr = "C:\\面向对象\\用户交易\\" + to_string(id) + "用户交易记录.txt";
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
	string time = str;//时间
	int pos = get_pos(id, bank);
	double money = bank->customer[pos].all_money;
	cout << "您的余额为" << money << endl;
	cout << "要取出多少钱" << endl;
	double _money;
	cin >> _money;
	while (money - _money < 0)
	{
		cout << "余额不足重新输入" << endl;
		cin >> _money;
	}
	money -= _money;
	string strs = to_string(money);
	string record = time + "取款" + strs + '\n';
	//修改数据
	modify(bank, money, record, pos);
	string strr = "C:\\面向对象\\用户交易\\" + to_string(id) + "用户交易记录.txt";
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
	string time = str;//时间
	int pos = get_pos(id, bank);
	double money = bank->customer[pos].all_money;
	cout << "您的余额为" << money << endl;
	string strs = to_string(money);
	string record = time + "查寻余额" + strs + '\n';
	string strr = "C:\\面向对象\\用户交易\\" + to_string(id) + "用户交易记录.txt";
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
	string time = str;//时间
	cout << "请输入你要转账的id:" << endl;
	int _id;
	cin >> _id;
	int pos = get_pos(_id, bank);
	while (pos == -1 && id != _id)
	{
		cout << "该用户不存在,重新输入或者不能给自己转账,请重新输入id" << endl;
		cin >> _id;
		pos = get_pos(_id, bank);
	}
	int _pos = get_pos(id, bank);
	double money = bank->customer[_pos].all_money;
	cout << "您的余额为" << money << endl;
	cout << "要转出多少钱" << endl;
	double _money;
	cin >> _money;
	while (money - _money < 0)
	{
		cout << "余额不足重新输入" << endl;
		cin >> _money;
	}
	money -= _money;

	string num = to_string(_money);//转的钱
	string people = to_string(_id);
	string record = time + "转帐" + num + "给" + people;

	//修改数据
	bank->customer[_pos].all_money -= _money;
	bank->customer[pos].all_money += _money;
	string strr = "C:\\面向对象\\用户交易\\" + to_string(id) + "用户交易记录.txt";
	const char* road = strr.data();
	FILE* fp = fopen(road, "a");
	fprintf(fp, "%s", &record[0]);
	fclose(fp);
}
void show_trade(Bank* bank, int id)
{
	string add;
	string record;

	cout << "以下为用户" << id << "的交易记录" << endl;
	string strr = "C:\\面向对象\\用户交易\\" + to_string(id) + "用户交易记录.txt";
	ifstream fppp(strr);
	while (getline(fppp, record)) {
		add += record;
		add += "      \n";
	}
	cout << add << endl << endl;
	fppp.close();
}
void save(Bank* bank, int id)//保存余额
{
	int pos = get_pos(id, bank);
	string str = "C:\\面向对象\\用户信息\\用户信息.txt";
	const char* Road = str.data();
	FILE* fp = fopen(Road, "w");
	for (int x = 0; x < bank->customer.size(); ++x)
	{
		fprintf(fp, "%d    %lf\n", bank->customer[x].id, bank->customer[x].all_money);
	}
	fclose(fp);
	return;
}