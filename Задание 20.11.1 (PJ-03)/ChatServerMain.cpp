#include "ChatServer.h"

int main() {
    int port = 9999; // You can choose any port you want
    ChatServer server(port);
    server.run();
    return 0;
}