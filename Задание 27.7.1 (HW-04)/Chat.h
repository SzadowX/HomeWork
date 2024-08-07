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
	void writeMessage(const std::string& sender);
	void messageHistory();

protected:
	std::string _login{}; // логин
	std::string _pass{}; // пароль
	std::string _name{}; // имя
};