#pragma once
#include <iostream>
#include <string>
#include <list>



class Chat{
public:
    Chat(){};
    
    /* методы чата для пользователя */
    void regUser(const std::string& _login, const std::string& _pass); // добавление нового пользователя
    bool authUser(const std::string& _login, const std::string& _pass); // авторизация
    void delUser(const std::string& _login); // удаление пользователя
    void showUsers(); // вывод списка пользователей
    int getIndex(const std::string& _login); // поиск индекса пользователя по имени
    bool logOut(const std::string& _login); // выход
    void userTyping(const std::string& _from, const std::string& _to); // написание сообщения
    
    /* сообщения */
    void getMsgs(const std::string& _from, const std::string& _to); // вывод истории сообщений

private:
    enum userStatus{
        online,
        offline
    };

    // класс пользователя
    struct User{
        User() : age(-1), status(userStatus::offline){}
        ~User(){}

        User(const std::string& _login, const std::string& _pass) : login(_login), pass(_pass), age(-1), status(userStatus::offline){}
        
        /* методы пользователя */
        std::string getStatus();
        void switchStatus();

        // переменные пользователя
        std::string login;
        std::string pass;

        std::string name;
        int age;
        userStatus status;
    };
    
    // класс сообщений
    struct Msg{ 
        Msg() : _msg(""){}
        Msg(const std::string& _from, const std::string& _to, const std::string& msg) : sender(_from), recipient(_to), _msg(msg){}
        
        // переменные класса сообщений
        std::string sender;
        std::string recipient;
        std::string _msg;
    };

    // хранение списка пользователей и сообщений
    std::list<User> _users;
    std::list<Msg> _messages;
};