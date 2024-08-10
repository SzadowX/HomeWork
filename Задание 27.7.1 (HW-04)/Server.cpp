#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include "Logger.h"
#include "mysql.h"

#pragma warning(disable: 4996)

SOCKET Connections[100];
int Counter = 0;
Logger logger("log.txt");

void MySQLStartup() {
    MYSQL mysql;
    mysql_init(&mysql);
    if (&mysql == NULL) {
        std::cout << "Error: can't create MySQL-descriptor\n";
    }
    if (!mysql_real_connect(&mysql, "localhost", "root", "root", "chatdb", 0, NULL, 0)) {
        std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
    } else {
        std::cout << "Success!\n";
    }
    mysql_close(&mysql);
}

void handleMessage(const std::string& sender, const std::string& recipient, const std::string& text) {
    MYSQL mysql;
    mysql_init(&mysql);

    if (!mysql_real_connect(&mysql, "localhost", "root", "root", "chatdb", 0, NULL, 0)) {
        std::string error = "Error: can't connect to database ";
        error += mysql_error(&mysql);
        std::cout << error << std::endl;
        return;
    }

    std::string insert_query = "INSERT INTO messages (sender, recipient, text) VALUES ('" + sender + "', '" + recipient + "', '" + text + "')";
    if (mysql_query(&mysql, insert_query.c_str()) == 0) {
        logger.logMessage(sender, recipient, text);
        std::cout << "Message logged successfully." << std::endl;
    } else {
        std::string error = "Error: ";
        error += mysql_error(&mysql);
        std::cout << error << std::endl;
    }

    mysql_close(&mysql);
}

void clientHandler(int index) {
    char buffer[256];
    while (true) {
        ZeroMemory(buffer, sizeof(buffer));
        int bytesReceived = recv(Connections[index], buffer, sizeof(buffer), NULL);
        //std::cout << "Принято сообщение такой длины: " << bytesReceived << std::endl;
        if (bytesReceived > 0) {
            std::string msg(buffer);
            size_t delimPos = msg.find('|');
            std::string sender = msg.substr(0, delimPos);
            size_t delimPos2 = msg.find('|', delimPos + 1);
            std::string recipient = msg.substr(delimPos + 1, delimPos2 - delimPos - 1);
            std::string text = msg.substr(delimPos2 + 1);

            handleMessage(sender, recipient, text);
        }
    }
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
    std::cout << "Server started on port: " << addr.sin_port << std::endl;
    MySQLStartup();

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);
    SOCKET newConnection;
    for (int i = 0; i < 100; i++) {
        newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

        if (newConnection == 0) {
            std::cout << "Error #2\n";
        } else {
            std::cout << "Client Connected!\n";
            Connections[i] = newConnection;
            Counter++;
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)clientHandler, (LPVOID)(i), NULL, NULL);
        }
    }
}

int main() {
    WSAStartup();
    system("pause");
    return 0;
}