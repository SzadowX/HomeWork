#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void showHelp() {
    std::cout << "[r]egister\tRegister a new user\n";
    std::cout << "[l]ogin\t\tLog in as a user\n";
    std::cout << "[s]end\t\tSend a message\n";
    std::cout << "[q]uit\t\tQuit the program\n";
}

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9999);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        perror("Invalid address");
        return 1;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    char buffer[1024] = {0};
    std::string command;

    while (true) {
        showHelp();
        std::cout << "Enter command: ";
        std::cin >> command;
        std::cin.ignore();

        if (command == "r") {
            std::string login, pass;
            std::cout << "Enter login: ";
            std::getline(std::cin, login);
            std::cout << "Enter password: ";
            std::getline(std::cin, pass);

            std::string message = "reg:" + login + ":" + pass;
            send(clientSocket, message.c_str(), message.size(), 0);
            read(clientSocket, buffer, 1024);
            std::cout << buffer << std::endl;

        } else if (command == "l") {
            std::string login, pass;
            std::cout << "Enter login: ";
            std::getline(std::cin, login);
            std::cout << "Enter password: ";
            std::getline(std::cin, pass);

            std::string message = "auth:" + login + ":" + pass;
            send(clientSocket, message.c_str(), message.size(), 0);
            read(clientSocket, buffer, 1024);
            std::cout << buffer << std::endl;

        } else if (command == "s") {
            std::string from, to, msg;
            std::cout << "Enter your login: ";
            std::getline(std::cin, from);
            std::cout << "Enter recipient login: ";
            std::getline(std::cin, to);
            std::cout << "Enter message: ";
            std::getline(std::cin, msg);

            std::string message = "msg:" + from + ":" + to + ":" + msg;
            send(clientSocket, message.c_str(), message.size(), 0);
            read(clientSocket, buffer, 1024);
            std::cout << buffer << std::endl;

        } else if (command == "q") {
            break;
        } else {
            std::cout << "Invalid command" << std::endl;
        }
    }

    close(clientSocket);
    return 0;
}