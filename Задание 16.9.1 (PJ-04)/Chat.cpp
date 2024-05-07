#include <iostream>
#include <string>
#include <list>
#include "Chat.h"

/* Чат */
// добавление
void Chat::regUser(const std::string& _login, const std::string& _pass){
    std::cout << "Создание аккаунта пользователя...";
    for(const auto& user : _users){
        if(user.login == _login){
            std::cout << "Ошибка\nЛогин занят, выберите другой логин!\n" << std::endl;
            return;
        }
    }

    User newUser(_login, _pass);
    _users.push_back(newUser);
    std::cout << "Успешно\nНовый пользователь добавлен!\n";
}

// авторизация
bool Chat::authUser(const std::string& _login, const std::string& _pass){
    std::cout << "Проверка данных пользователя...";
    for(auto& user : _users){
        if(user.login == _login && user.pass == _pass){
            user.switchStatus();
            std::cout << "Успешно\nДобро пожаловать!\n";
            return true;
        }
    }
    std::cout << "Ошибка\nНеверный логин или пароль!\n";
    return false;
}

// выход
bool Chat::logOut(const std::string& _login){
    for(auto& user : _users){
        if(user.login == _login){
            user.switchStatus();
            std::cout << "Пользователь вышел из чата!\n";
            return true;
        }
    }
    return false; 
}

// удаление
void Chat::delUser(const std::string& _login){
    std::cout << "Удаление данных пользователя...";
    for(auto it = _users.begin(); it != _users.end(); ++it){
        if(it->login == _login){
            _users.erase(it);
            std::cout << "Успешно\nДанные удалены!\n";
            return;
        }
    }
    std::cout << "Ошибка\nПользователь не найден!\n";
}

// функция написания сообщения
void Chat::userTyping(const std::string& _from, const std::string& _to){
    while(true){
        std::string msg_body;
        std::cout << _from << ": ";
        std::getline(std::cin, msg_body);

        if(msg_body == "q"){
            system("clear");
            break;
        }
        else{
            _messages.emplace_back(_from, _to, msg_body);
        }
    }
}

// вывод списка пользователей
void Chat::showUsers(){
    for(const auto& user : _users){
        std::cout << user.login << '\t' << user.name << '\t' << user.getStatus() << '\n';
    }
}

// поиск индекса (проверка существования пользователя) по логину
int Chat::getIndex(const std::string& _login){
    int index = 0;
    for(const auto& user : _users){
        if(user.login == _login){
            return index;
        }
        ++index;
    }
    std::cout << "Пользователь не найден!\n" << std::endl;
    return -1;
}

// вывод истории сообщений
void Chat::getMsgs(const std::string& _from, const std::string& _to){
    for(const auto& msg : _messages){
        if((_to == "all" || _to == msg.recipient) && (_from == msg.sender || _from == msg.recipient)){
            std::cout << msg.sender << ": " <<  msg._msg << std::endl;
        }
    }
}

/* пользователь*/
// пролучение данных статуса
std::string Chat::User::getStatus(){
    return (status == online) ? "online" : "offline";
}

// изменение статуса
void Chat::User::switchStatus(){
    status = (status == online) ? offline : online;
}