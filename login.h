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
int getch() {
    struct termios oldt{}, newt{};
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

using namespace std;


struct User {
    string nameandsur;
    string phone;
    string password;
};


bool isPhoneValid(const string& phone) {
    if (phone.length() != 10) return false;
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}


void getMaskedPassword(string& password, size_t maxLen) {
    char ch;
    password.clear();

    while (true) {
        ch = getch();

        if (ch == '\n' || ch == '\r') {
            cout << endl;
            break;
        }
        else if (ch == '\b' || ch == 127) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else if (ch == ' ') {
            continue;
        }
        else if (password.length() < maxLen - 1) {
            password += ch;
            cout << "*";
        }
    }
}


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void waitForEnter() {
    cout << "Press Enter for next function ";
    while (true) {
        char input = getchar();
        if (input == '\n') {
            clearScreen();
            break;
        } else {
            cout << "Invalid input. Please press Enter only.\n";
            while (getchar() != '\n');
        }
    }
}


void saveLogin(const User& currentUser) {
    ofstream file("user.txt");
    if (!file) {
        cout << "Error saving login session.\n";
        return;
    }
    file << currentUser.nameandsur << " " << currentUser.phone;
}


bool loadLogin(User& currentUser) {
    ifstream file("logindata.txt");
    if (!file) return false;
    file >> currentUser.nameandsur >> currentUser.phone;
    return true;
}

void logoutUser(User& currentUser) {
    if (loadLogin(currentUser)) {
        remove("logindata.txt");
        cout << "You have been logged out.\n";
    } else {
        cout << "You are not logged in.\n";
    }
}


void saveUsers(const vector<User>& users) {
    ofstream file("user.txt");
    for (const auto& user : users) {
        file << user.nameandsur << " " << user.phone << " " << user.password << endl;
    }
    cout << "Data saved successfully!\n";
}


void registerUser(User& currentUser) {
    ofstream file("user.txt", ios::app);
    if (!file) {
        cout << "Cannot open file.\n";
        return;
    }

    User newUser;
    cout << "Enter your Name-Surname: ";
    getline(cin, newUser.nameandsur);

    int back;
    bool isDuplicate;

    do {
        cout << "Enter your phone number (10 digits): ";
        getline(cin, newUser.phone);

        if (!isPhoneValid(newUser.phone)) {
            cout << "Invalid phone number. Please enter a valid 10-digit phone number.\n";
            do {
                cout << "Enter your choice (1 to continue, 2 to exit): ";
                cin >> back;
                cin.ignore();
                if (back == 2) {
                    clearScreen();
                    return;
                }
            } while (back != 1);
            continue;
        }

        ifstream checkFile("user.txt");
        string line;
        isDuplicate = false;
        while (getline(checkFile, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            string existingPhone = line.substr(pos1 + 1, pos2 - pos1 - 1);
            if (existingPhone == newUser.phone) {
                isDuplicate = true;
                cout << "This phone number is already registered.\n";
                do {
                    cout << "Enter your choice (1 to continue, 2 to exit): ";
                    cin >> back;
                    cin.ignore();
                    if (back == 2) {
                        clearScreen();
                        return;
                    }
                } while (back != 1);
                break;
            }
        }
    } while (isDuplicate || !isPhoneValid(newUser.phone));

    string confirmPass;
    do {
        cout << "Enter your password: ";
        getMaskedPassword(newUser.password, 20);

        if (newUser.password.length() < 8) {
            cout << "Password needs to be at least 8 characters.\n";
        } else if (newUser.password.length() > 20) {
            cout << "Password needs to be less than 20 characters.\n";
        } else if (newUser.password.find(' ') != string::npos) {
            cout << "Password cannot contain spaces!\n";
        } else {
            break;
        }
    } while (true);

    do {
        cout << "Confirm your password: ";
        getMaskedPassword(confirmPass, 20);
        if (confirmPass != newUser.password) {
            cout << "Passwords do not match!\n";
        }
    } while (confirmPass != newUser.password);

    file << newUser.nameandsur << "|" << newUser.phone << "|" << newUser.password << endl;
    ofstream courseFile(newUser.phone + ".txt");
    courseFile.close();

    cout << "\nRegistration successful! Your username (phone) is " << newUser.phone << endl;
    waitForEnter();
}


bool loginUser(User& currentUser) {
    ifstream file("user.txt");
    if (!file) {
        cout << "Cannot open the file.\n";
        return false;
    }

    vector<User> users;
    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos) continue;

        User temp;
        temp.nameandsur = line.substr(0, pos1);
        temp.phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
        temp.password = line.substr(pos2 + 1);

        users.push_back(temp);
    }

    string phone, password;
    cout << "Enter your phone number: ";
    getline(cin, phone);
    cout << "Enter your password: ";
    getMaskedPassword(password, 20);

    for (const auto& user : users) {
        if (user.phone == phone && user.password == password) {
            currentUser = user;

            cout << "\nLogin Successful! Welcome " << user.nameandsur << endl;
            saveLogin(currentUser);
            return true;
        }
    }
        cout << "Phone number or password incorrect.\n";
        return false;
}



#endif
