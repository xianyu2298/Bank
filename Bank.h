#pragma once
#include<iostream>
#include<stdio.h>
#include <ctime>//时间生成函数用于生成时间
#include<vector>
#include<stdlib.h>
#include<string>
#include<conio.h>
#include<fstream>
#include <chrono>
using namespace std;


class Customer { //顾客类
public:

	int id;//顾客的序号
	int passport;//少于6位
	double all_money;//顾客账户的总金额
	string trade_record;//用于保存交易记录
};

class Bank {

public:
	vector<Customer> customer;
};
void zhuce();//注册
void Init(Bank* bank);//加载初始化文件
void deposit(Bank* bank, int id);//存款
void withdraw(Bank* bank, int id);//取款
void show_money(Bank* bank, int id);//查询余额
void change_money(Bank* bank, int id);//用户转账
void show_trade(Bank* bank, int id);//用户交易
void save(Bank* bank, int id);//退出保存#pragma once
