#pragma once
#include<iostream>
#include<stdio.h>
#include <ctime>//ʱ�����ɺ�����������ʱ��
#include<vector>
#include<stdlib.h>
#include<string>
#include<conio.h>
#include<fstream>
#include <chrono>
using namespace std;


class Customer { //�˿���
public:

	int id;//�˿͵����
	int passport;//����6λ
	double all_money;//�˿��˻����ܽ��
	string trade_record;//���ڱ��潻�׼�¼
};

class Bank {

public:
	vector<Customer> customer;
};
void zhuce();//ע��
void Init(Bank* bank);//���س�ʼ���ļ�
void deposit(Bank* bank, int id);//���
void withdraw(Bank* bank, int id);//ȡ��
void show_money(Bank* bank, int id);//��ѯ���
void change_money(Bank* bank, int id);//�û�ת��
void show_trade(Bank* bank, int id);//�û�����
void save(Bank* bank, int id);//�˳�����#pragma once
