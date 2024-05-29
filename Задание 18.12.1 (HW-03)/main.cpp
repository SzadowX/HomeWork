#include <iostream>
#include "User.h"
#include "Message.h"

int main() {
    User user1("Alice", "alice123", "password");
    User user2("Bob", "bob321", "12345");

    user1.saveToFile("User.txt");
    user2.saveToFile("User.txt");

    Message msg1("Hello, Bob!", "Alice", "Bob");
    Message msg2("Hi, Alice!", "Bob", "Alice");

    msg1.saveToFile("Message.txt");
    msg2.saveToFile("Message.txt");

    std::cout << "User and Message objects saved to files." << std::endl;

    return 0;
}