#pragma once
#include <string>
#include "mysql.h"

class Chat {
public:
	Chat() {};
	~Chat() {};
	void regUser();
	bool logIn();
	void showUsers();
	void writeMessage();
	void messageHistory();

protected:
	std::string _login{}; // �����
	std::string _pass{}; // ������
	std::string _name{}; // ���
};