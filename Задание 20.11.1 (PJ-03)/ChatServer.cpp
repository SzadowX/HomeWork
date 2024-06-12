#include "ChatServer.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <algorithm>

ChatServer::ChatServer(int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 10) < 0) {
        perror("Listen failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server started on port " << port << std::endl;
}

ChatServer::~ChatServer() {
    close(serverSocket);
    for (int clientSocket : clientSockets) {
        close(clientSocket);
    }
}

void ChatServer::run() {
    fd_set readfds;

    while (true) {
        FD_ZERO(&readfds);
        FD_SET(serverSocket, &readfds);
        int max_sd = serverSocket;

        for (int clientSocket : clientSockets) {
            FD_SET(clientSocket, &readfds);
            if (clientSocket > max_sd) {
                max_sd = clientSocket;
            }
        }

        int activity = select(max_sd + 1, &readfds, nullptr, nullptr, nullptr);
        if ((activity < 0) && (errno != EINTR)) {
            perror("Select error");
        }

        if (FD_ISSET(serverSocket, &readfds)) {
            handleNewConnection();
        }

        for (auto it = clientSockets.begin(); it != clientSockets.end(); ) {
            if (FD_ISSET(*it, &readfds)) {
                if (!handleClientMessage(*it)) {
                    close(*it);
                    it = clientSockets.erase(it);
                    std::cout << "Client disconnected" << std::endl;
                } else {
                    ++it;
                }
            } else {
                ++it;
            }
        }
    }
}

void ChatServer::handleNewConnection() {
    int newSocket = accept(serverSocket, nullptr, nullptr);
    if (newSocket < 0) {
        perror("Accept failed");
        return;
    }
    clientSockets.push_back(newSocket);
    std::cout << "New connection accepted" << std::endl;
}

bool ChatServer::handleClientMessage(int clientSocket) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    int bytesRead = read(clientSocket, buffer, sizeof(buffer));
    if (bytesRead <= 0) {
        return false;  // Client disconnected
    } else {
        std::string message(buffer);
        processClientMessage(clientSocket, message);
        return true;  // Message handled successfully
    }
}

void ChatServer::processClientMessage(int clientSocket, const std::string& message) {
    std::cout << "Received message: " << message << std::endl;

    std::string response;
    if (message.substr(0, 4) == "reg:") {
        size_t delim = message.find(':', 4);
        std::string login = message.substr(4, delim - 4);
        std::string pass = message.substr(delim + 1);
        chat.regUser(login, pass);
        response = "User registered: " + login;
    } else if (message.substr(0, 5) == "auth:") {
        size_t delim = message.find(':', 5);
        std::string login = message.substr(5, delim - 5);
        std::string pass = message.substr(delim + 1);
        if (chat.authUser(login, pass)) {
            response = "User authenticated: " + login;
        } else {
            response = "Authentication failed for user: " + login;
        }
    } else if (message.substr(0, 4) == "msg:") {
        size_t delim1 = message.find(':', 4);
        size_t delim2 = message.find(':', delim1 + 1);
        std::string from = message.substr(4, delim1 - 4);
        std::string to = message.substr(delim1 + 1, delim2 - delim1 - 1);
        std::string msg_body = message.substr(delim2 + 1);
        chat.userTyping(from, to, msg_body);
        response = "Message from " + from + " to " + to + ": " + msg_body;
    } else {
        response = "Invalid message format.";
    }

    sendMessageToClient(clientSocket, response);
}

void ChatServer::sendMessageToClient(int clientSocket, const std::string& message) {
    write(clientSocket, message.c_str(), message.size());
}