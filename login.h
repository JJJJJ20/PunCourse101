#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

struct User {
    string nameandsur;
    string phone;
    string password;
};

class LoginSystem {
public:
    int getch();
    bool isPhoneValid(const string& phone);
    bool isNameValid(const string& name);
    void getMaskedPassword(string& password, size_t maxLen);
    void clearScreen();
    void waitForEnter();


    void registerUser(User& currentUser);
    bool loginUser(User& currentUser);
};

#endif
