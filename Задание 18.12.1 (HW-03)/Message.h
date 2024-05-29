#pragma once
#include <string>

class Message {
private:
    std::string _text;
    std::string _sender;
    std::string _receiver;
public:
    Message(const std::string &text, const std::string &sender, const std::string &receiver);

    std::string getText() const;
    std::string getSender() const;
    std::string getReceiver() const;

    void saveToFile(const std::string &filename) const;
};