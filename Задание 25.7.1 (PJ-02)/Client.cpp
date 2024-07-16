#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include "Chat.h"

#pragma warning(disable: 4996)

int WSAStartup() {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(9999);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 0;
	}
	std::cout << "Connected!\n";
}

void userHelp() {
	std::cout << "[r]egister\tдля регистрации нового пользователя\n[l]ogin\tдля входа в аккаунт\n[c]atalog\tдля вывода списка пользователей\n[h]elp\tдля вывода списка команд\n[q]uit\tдля выхода из программы\n";
}

int main() {
	setlocale(LC_ALL, "RU");

	if (WSAStartup())
	{
		Chat chat;
		std::cout << "---------- Добро пожаловать в чат ----------\n";
		bool running = true;
		while (running)
		{
			std::cout << "Для работы с программой используйте:\n";
			userHelp();
			std::cout << "Главное меню: ";
			char choice;
			std::cin >> choice;
			std::cin.ignore(256, '\n'); // игнорирование ввода символов после первого

			switch (choice) {
			case 'r':
				chat.regUser();
				break;
			case 'l':
				if (!chat.logIn()) {
					choice = ' ';
					break;
				}
			case 'c':
				system("cls");
				std::cout << "Список пользователей:\n";
				chat.showUsers();
				std::cout << "----------\n\n";
				break;
			case 'q':
				running = false;
				break;
			default:
				system("cls");
				std::cout << "Неверное значение!\n";
				break;
			}
		}
	}
	system("pause");
	return 0;
}