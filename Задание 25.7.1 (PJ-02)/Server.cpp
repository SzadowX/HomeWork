#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include "Chat.h"

#pragma warning(disable: 4996)

SOCKET Connections[100];
int Counter = 0;

void MySQLStartup() {
	MYSQL mysql; // Дескриптор соединения c MySql
	mysql_init(&mysql);
	if (&mysql == NULL) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		std::cout << "Error: can't create MySQL-descriptor\n";
	}
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", "chatdb", 0, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
	}
	else {
		// Если соединение успешно установлено выводим фразу — "Success!"
		std::cout << "Success connect to database!\n";
	}
	mysql_close(&mysql);
}

void WSAStartup() {
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
	std::cout << "Server started!\n";
	MySQLStartup();

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);
	SOCKET newConnection;
	for (int i = 0; i < 100; i++)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (newConnection == 0) {
			std::cout << "Error #2\n";
		}
		else {
			std::cout << "Client Connected!\n";
			Connections[i] = newConnection;
			Counter++;
		}
	}
}

int main() {
	WSAStartup();
	system("pause");
	return 0;
}