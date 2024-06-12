#pragma once
#include <iostream>
#include <string>
#include <list>

class Chat {
public:
    Chat() {};

    void regUser(const std::string& _login, const std::string& _pass);
    bool authUser(const std::string& _login, const std::string& _pass);
    void delUser(const std::string& _login);
    void showUsers();
    int getIndex(const std::string& _login);
    bool logOut(const std::string& _login);
    void userTyping(const std::string& _from, const std::string& _to, const std::string& msg);
    void getMsgs(const std::string& _from, const std::string& _to);

private:
    enum userStatus {
        online,
        offline
    };

    struct User {
        User() : age(-1), status(userStatus::offline) {}
        ~User() {}

        User(const std::string& _login, const std::string& _pass)
            : login(_login), pass(_pass), age(-1), status(userStatus::offline) {}

        std::string getStatus();
        void switchStatus();

        std::string login;
        std::string pass;
        std::string name;
        int age;
        userStatus status;
    };

    struct Msg {
        Msg() : _msg("") {}
        Msg(const std::string& _from, const std::string& _to, const std::string& msg)
            : sender(_from), recipient(_to), _msg(msg) {}

        std::string sender;
        std::string recipient;
        std::string _msg;
    };

    std::list<User> _users;
    std::list<Msg> _messages;
};