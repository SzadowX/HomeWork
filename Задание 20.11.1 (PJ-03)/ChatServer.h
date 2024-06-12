#pragma once
#include <vector>
#include <netinet/in.h>
#include "Chat.h"

class ChatServer {
public:
    ChatServer(int port);
    ~ChatServer();
    void run();

private:
    int serverSocket;
    struct sockaddr_in serverAddr;
    std::vector<int> clientSockets;
    Chat chat;

    void handleNewConnection();
    bool handleClientMessage(int clientSocket);
    void processClientMessage(int clientSocket, const std::string& message);
    void sendMessageToClient(int clientSocket, const std::string& message);
};