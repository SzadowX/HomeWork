#pragma once
#include <string>

class User {
private:
    std::string _name;
    std::string _login;
    std::string _pass;
public:
    User(const std::string &name, const std::string &login, const std::string &pass);

    std::string getName() const;
    std::string getLogin() const;
    std::string getPass() const;

    void saveToFile(const std::string &filename) const;
};