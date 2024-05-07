#include <iostream>
#include <string>
#include "Chat.h"
using namespace std;

void userHelp(){
    cout << "[r]egistration\tдля регистрации нового пользователя\n[l]og in\tдля входа в аккаунт\n[c]atalog\tдля вывода списка пользователей\n[q]uit\tдля выхода из программы\n" << endl;
}

int main(){
    Chat chat;
        
    cout << "---------- Добро пожаловать в чат ----------" << endl;
    cout << "Для работы с программой используйте:\n";

    bool running = true;
    while(running){
        // переменные для логина и пароля
        std::string login, pass;
    
        userHelp();
        cout << "Главное меню: ";
        char choice;
        cin >> choice; // выбор действий пользователя
        cin.ignore(256, '\n'); // игнорирование ввода символов после первого
        
        // опции
        switch(choice){
            case 'r':
                system("clear");
                cout << "Регистрация нового пользователя\n";
                cout << "Придумайте логин: ";
                getline(cin, login);
                
                cout << "Придумайте пароль: ";
                getline(cin, pass);

                chat.regUser(login, pass);
                break;
            case 'l':
                system("clear");
                cout << "Авторизация пользователя\n";
                cout << "Введите логин: ";
                getline(cin, login);
                
                cout << "Введите пароль: ";
                getline(cin, pass);

                if(chat.authUser(login, pass)){
                    // отправка сообщений
                    while(true){
                        // выбор собеседника (чата)    
                        cout << "Введите имя собеседника ([q]uit для выхода):\n----------\nall\t(общий диалог)\n";
                        chat.showUsers();
                        
                        cout << login << ": "; // имя отправителя
                        std::string to;
                        getline(cin, to);
                        
                        // отмена
                        if(to == "q"){
                            chat.logOut(login);
                            break;
                        }

                        system("clear");
                        if(to == "all"){
                            cout << "---------- Групповой чат ----------" << endl;
                        }
                        else if(chat.getIndex(to) < 0){ continue; }
                        else{
                            cout << "---------- Собеседник  " << to << " ----------" << endl; 
                        }
                        chat.getMsgs(login, to); // история сообщений
                        chat.userTyping(login, to); // отправка сообщений
                    }
                }   
                break;
            case 'c':
                system("clear");
                cout << "Список пользователей:\n----------\nлогин\tимя\tстатус\n";
                chat.showUsers();
                cout << "----------\n\n";
                break;
            case 'q':
                running = false;
                break;
            default:
                system("clear");
                cout << "Неверное значение!\n";
                break;
        }
    }
    return 0;
}