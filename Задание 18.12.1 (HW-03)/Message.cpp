#include "Message.h"
#include <fstream>

Message::Message(const std::string &text, const std::string &sender, const std::string &receiver)
    : _text(text), _sender(sender), _receiver(receiver) {}

std::string Message::getText() const {
    return _text;
}

std::string Message::getSender() const {
    return _sender;
}

std::string Message::getReceiver() const {
    return _receiver;
}

void Message::saveToFile(const std::string &filename) const {
    std::ofstream ofs(filename, std::ios::app);
    if (ofs.is_open()) {
        ofs << "Text: " << _text << std::endl;
        ofs << "Sender: " << _sender << std::endl;
        ofs << "Receiver: " << _receiver << std::endl;
        ofs << "----------------------" << std::endl;
        ofs.close();
    }
}