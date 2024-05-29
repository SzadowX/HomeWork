#include "User.h"
#include <fstream>

User::User(const std::string &name, const std::string &login, const std::string &pass)
    : _name(name), _login(login), _pass(pass) {}

std::string User::getName() const {
    return _name;
}

std::string User::getLogin() const {
    return _login;
}

std::string User::getPass() const {
    return _pass;
}

void User::saveToFile(const std::string &filename) const {
    std::ofstream ofs(filename, std::ios::app);
    if (ofs.is_open()) {
        ofs << "Name: " << _name << std::endl;
        ofs << "Login: " << _login << std::endl;
        ofs << "Pass: " << _pass << std::endl;
        ofs << "----------------------" << std::endl;
        ofs.close();
    }
}