#include <iostream>
#include <string>
#include <list>
#include "Chat.h"

void Chat::regUser(const std::string& _login, const std::string& _pass) {
    for (const auto& user : _users) {
        if (user.login == _login) {
            std::cout << "Ошибка: Логин занят\n";
            return;
        }
    }

    User newUser(_login, _pass);
    _users.push_back(newUser);
    std::cout << "Успешно: Пользователь зарегистрирован\n";
}

bool Chat::authUser(const std::string& _login, const std::string& _pass) {
    for (auto& user : _users) {
        if (user.login == _login && user.pass == _pass) {
            user.switchStatus();
            std::cout << "Успешно: Авторизация прошла успешно\n";
            return true;
        }
    }
    std::cout << "Ошибка: Неверный логин или пароль\n";
    return false;
}

bool Chat::logOut(const std::string& _login) {
    for (auto& user : _users) {
        if (user.login == _login) {
            user.switchStatus();
            std::cout << "Пользователь вышел из чата\n";
            return true;
        }
    }
    return false;
}

void Chat::delUser(const std::string& _login) {
    for (auto it = _users.begin(); it != _users.end(); ++it) {
        if (it->login == _login) {
            _users.erase(it);
            std::cout << "Успешно: Пользователь удален\n";
            return;
        }
    }
    std::cout << "Ошибка: Пользователь не найден\n";
}

void Chat::userTyping(const std::string& _from, const std::string& _to, const std::string& msg) {
    _messages.emplace_back(_from, _to, msg);
}

void Chat::showUsers() {
    for (const auto& user : _users) {
        std::cout << user.login << '\t' << user.name << '\t' << user.status << '\n';
    }
}

int Chat::getIndex(const std::string& _login) {
    int index = 0;
    for (const auto& user : _users) {
        if (user.login == _login) {
            return index;
        }
        ++index;
    }
    std::cout << "Пользователь не найден\n";
    return -1;
}

void Chat::getMsgs(const std::string& _from, const std::string& _to) {
    for (const auto& msg : _messages) {
        if ((_to == "all" || _to == msg.recipient) && (_from == msg.sender || _from == msg.recipient)) {
            std::cout << msg.sender << ": " << msg._msg << std::endl;
        }
    }
}

std::string Chat::User::getStatus() {
    return (status == online) ? "online" : "offline";
}

void Chat::User::switchStatus() {
    status = (status == online) ? offline : online;
}