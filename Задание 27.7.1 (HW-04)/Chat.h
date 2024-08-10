#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
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
	void getSocket(SOCKET& con);

protected:
	std::string _login{}; // �����
	std::string _pass{}; // ������
	std::string _name{}; // ���
	SOCKET Connection;
};