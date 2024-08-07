#include <iostream>
#include <string>
#include "Chat.h"
#include <winsock2.h>

extern SOCKET Connection;

void Chat::regUser() {
    MYSQL mysql;
    mysql_init(&mysql);

    if (!mysql_real_connect(&mysql, "localhost", "root", "root", "chatdb", 0, NULL, 0)) {
        std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
        return;
    }

    system("cls");
    std::cout << "---------- ����������� ������ ������������ ----------\n[q]uit ��� ������\n����� � ������ �� ������ ��������� ��������\n";
    while (true) {
        std::cout << "\n������� �����: ";
        std::cin >> _login;
        std::cout << "\n������� ������: ";
        std::cin >> _pass;
        std::cout << "\n���������� ���: ";
        std::cin >> _name;

        if (_login == "q" || _pass == "q" || _name == "q") { // ������ ������
            std::cout << "----- ������!\n" << std::endl;
            break;
        }

        std::string check_query = "SELECT COUNT(*) FROM users WHERE login = '" + _login + "'";
        if (mysql_query(&mysql, check_query.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(&mysql);
            MYSQL_ROW row = mysql_fetch_row(res);
            if (std::stoi(row[0]) > 0) {
                std::cout << "----- ����� ��� ����������. ����������, �������� ������.\n" << std::endl;
                mysql_free_result(res);
                continue;
            }
            mysql_free_result(res);
        }
        else {
            std::cout << "Error: " << mysql_error(&mysql) << std::endl;
            break;
        }

        std::string insert_query = "INSERT INTO users (login, passwd, name) VALUES ('" + _login + "', '" + _pass + "', '" + _name + "')";
        if (mysql_query(&mysql, insert_query.c_str()) == 0) {
            std::cout << "----- ������������ " << _login << " ���������������\n" << std::endl;
        }
        else {
            std::cout << "Error: " << mysql_error(&mysql) << std::endl;
        }
        break;
    }

    mysql_close(&mysql);
}

bool Chat::logIn() {
    MYSQL mysql;
    mysql_init(&mysql);

    if (!mysql_real_connect(&mysql, "localhost", "root", "root", "chatdb", 0, NULL, 0)) {
        std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
        return 1;
    }

    system("cls");
    std::cout << "---------- ����������� ----------\n";
    while (true) {
        std::cout << "\n������� �����: ";
        std::cin >> _login;

        if (_login == "q") { // ������ ������
            std::cout << "----- ������!\n" << std::endl;
            system("cls");
            return 0;
        }

        std::cout << "\n������� ������: ";
        std::cin >> _pass;

        std::string check_query = "SELECT COUNT(*) FROM users WHERE login = '" + _login + "' AND passwd = '" + _pass + "'";
        if (mysql_query(&mysql, check_query.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(&mysql);
            MYSQL_ROW row = mysql_fetch_row(res);
            if (std::stoi(row[0]) > 0) {
                std::cout << "----- ����������� �������. ����� ����������, " << _login << "!\n" << std::endl;
            }
            else {
                std::cout << "----- ������������ ����� ��� ������. ����������, ���������� �����.\n" << std::endl;
                mysql_free_result(res);
                continue;
            }
            mysql_free_result(res);
        }
        else {
            std::cout << "Error: " << mysql_error(&mysql) << std::endl;
            break;
        }
        break;
    }

    mysql_close(&mysql);
    bool running = true;
    while (true)
    {
        std::cout << "[w]rite\t��� ��������� ���������\n[h]istory\t��� ������ ������� ���������\n[q]uit\t��� �������� � ������� ����\n";
        char choice;
        std::cin >> choice;
        std::cin.ignore(256, '\n'); // ������������� ����� �������� ����� �������
        switch (choice)
        {
        case 'w':
            writeMessage(_login);
            break;
        case 'h':
            messageHistory();
            break;
        case 'q':
            return 1;
            break;
        default:
            system("cls");
            std::cout << "�������� ��������!\n";
            break;
        }
    }
}

void Chat::writeMessage(const std::string& sender) {
    MYSQL mysql;
    mysql_init(&mysql);

    if (!mysql_real_connect(&mysql, "localhost", "root", "root", "chatdb", 0, NULL, 0)) {
        std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
        return;
    }

    std::string recipient, text;
    std::cout << "������� ��� ����������: ";
    std::cin >> recipient;
    std::cout << "������� ���������: ";
    std::cin.ignore(); // ���������� ���������� ������ ����� ������ ����� ����������� �����
    std::getline(std::cin, text); // ���������� getline ��� ����� ������ � ���������

    // ��������� ������������� ����������
    std::string check_query = "SELECT COUNT(*) FROM users WHERE login = '" + recipient + "'";
    if (mysql_query(&mysql, check_query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(&mysql);
        MYSQL_ROW row = mysql_fetch_row(res);
        if (std::stoi(row[0]) > 0) {
            std::string insert_query = "INSERT INTO messages (sender, recipient, text) VALUES ('" + _login + "', '" + recipient + "', '" + text + "')";
            if (mysql_query(&mysql, insert_query.c_str()) == 0) {
                std::cout << "----- ��������� ����������!\n" << std::endl;
		    std::string msg = sender + "|" + recipient + "|" + text;
    		send(Connection, msg.c_str(), msg.length(), 0);
            }
            else {
                std::cout << "Error: " << mysql_error(&mysql) << std::endl;
            }
        }
        else {
            std::cout << "----- ���������� �� ������. ����������, ��������� ��� ����������.\n" << std::endl;
        }
        mysql_free_result(res);
    }
    else {
        std::cout << "Error: " << mysql_error(&mysql) << std::endl;
    }

    mysql_close(&mysql);
}

void Chat::messageHistory() {
    MYSQL mysql;
    mysql_init(&mysql);

    if (!mysql_real_connect(&mysql, "localhost", "root", "root", "chatdb", 0, NULL, 0)) {
        std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
        return;
    }

    // ������ �� ��������� ��������� ��� ����������� ������������
    std::string query = "SELECT * FROM messages WHERE sender = '" + _login + "' OR recipient = '" + _login + "'";
    if (mysql_query(&mysql, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(&mysql);
        MYSQL_ROW row;

        std::cout << "������� ��������� ��� ������������ " << _login << ":\n";
        while ((row = mysql_fetch_row(res))) {
            std::cout << "ID: " << row[0] << " | �����������: " << row[1] << " | ����������: " << row[2] << " | ���������: " << row[3] << std::endl;
            std::cout << std::endl;
        }
        mysql_free_result(res);
    }
    else {
        std::cout << "Error: " << mysql_error(&mysql) << std::endl;
    }

    mysql_close(&mysql);
}

void Chat::showUsers() {
    MYSQL mysql;
    mysql_init(&mysql);
    if (mysql_real_connect(&mysql, "localhost", "root", "root", "chatdb", 0, NULL, 0)) {
        mysql_query(&mysql, "SELECT name, login FROM users");
        MYSQL_RES* res = mysql_store_result(&mysql);
        if (res) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res))) {
                std::cout << "Name: " << row[0] << " Login: " << row[1] << std::endl;
            }
            mysql_free_result(res);
        }
        mysql_close(&mysql);
    }
    else {
        std::cout << "Error: " << mysql_error(&mysql) << std::endl;
    }
}