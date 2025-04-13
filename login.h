// login.h
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

int getch();
bool isPhoneValid(const string& phone);
bool isNameValid(const string& name);
void getMaskedPassword(string& password, size_t maxLen);
void clearScreen();
void waitForEnter();
void saveLogin(const User& currentUser);
bool loadLogin(User& currentUser);
void logoutUser(User& currentUser);
void saveUsers(const vector<User>& users);
void registerUser(User& currentUser);
bool loginUser(User& currentUser);

#endif
