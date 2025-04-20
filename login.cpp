#include "login.h"
#include <algorithm>

#ifndef _WIN32
int LoginSystem::getch() {
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

bool LoginSystem::isPhoneValid(const string& phone) {
    return phone.length() == 10 &&
           phone[0] == '0' &&
           all_of(phone.begin(), phone.end(), ::isdigit);
}

bool LoginSystem::isNameValid(const string& name) {
    return !name.empty() && all_of(name.begin(), name.end(), [](char c) {
        return isalpha(c) || c == ' ' || (unsigned char)c >= 0xA0;
    });
}

void LoginSystem::getMaskedPassword(string& password, size_t maxLen) {
    char ch;
    password.clear();
    while (true) {
        ch = getch();
        if (ch == '\n' || ch == '\r') {
            cout << endl;
            break;
        } else if (ch == '\b' || ch == 127) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else if (ch == ' ') {
            continue;
        } else if (password.length() < maxLen - 1) {
            password += ch;
            cout << "*";
        }
    }
    tcflush(STDIN_FILENO, TCIFLUSH);
}

void LoginSystem::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void LoginSystem::waitForEnter() {
    cout << "Press Enter for next function ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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



bool LoginSystem::loadLogin(User& currentUser) {
    ifstream file("logindata.txt");
    if (!file) return false;
    file >> currentUser.nameandsur >> currentUser.phone;
    return true;
}

void LoginSystem::logoutUser(User& currentUser) {
    if (loadLogin(currentUser)) {
        remove("logindata.txt");
        cout << "You have been logged out.\n";
    } else {
        cout << "You are not logged in.\n";
    }
}

void LoginSystem::saveUsers(const vector<User>& users) {
    ofstream file("user.txt");
    for (const auto& user : users) {
        file << user.nameandsur << "|" << user.phone << "|" << user.password << endl;
    }
}

void LoginSystem::registerUser(User& currentUser) {
    ofstream file("user.txt", ios::app);
    if (!file) {
        cout << "Cannot open file.\n";
        return;
    }

    User newUser;

    do {
        cout << "Enter your Name-Surname: ";
        getline(cin, newUser.nameandsur);
        if (!isNameValid(newUser.nameandsur))
            cout << "Invalid input. Please use letters only.\n";
    } while (!isNameValid(newUser.nameandsur));

    bool isDuplicate = false;
    do {
        cout << "Enter your phone number (10 digits): ";
    getline(cin, newUser.phone);

    if (!isPhoneValid(newUser.phone)) {
        if (newUser.phone.length() != 10)
            cout << "❌ Phone number must be exactly 10 digits.\n";
        else if (!all_of(newUser.phone.begin(), newUser.phone.end(), ::isdigit))
            cout << "❌ Phone number must contain digits only (no letters or symbols).\n";
        else if (newUser.phone[0] != '0')
            cout << "❌ Phone number must start with 0.\n";

        cout << "Press Enter to try again...";
        while (getchar() != '\n');
        clearScreen();
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
                cout << "Phone already registered.\n";
                cout << "Press Enter to try again...";
                while (getchar() != '\n');
                clearScreen(); 
                break;
            }
        }
        if (isDuplicate) continue;

    } while (!isPhoneValid(newUser.phone) || isDuplicate);

    string confirmPass;
    do {
        cout << "Enter your password: ";
        getMaskedPassword(newUser.password, 20);
        tcflush(STDIN_FILENO, TCIFLUSH);
    
        if (newUser.password.length() < 8) {
            cout << "❌ Your password must be at least 8 characters.\n";
            continue;
        }
    
        if (newUser.password.find(' ') != string::npos) {
            cout << "❌ Password cannot contain spaces.\n";
            continue;
        }
    
        cout << "Confirm your password: ";
        getMaskedPassword(confirmPass, 20);
    
        if (confirmPass != newUser.password) {
            cout << "❌ Passwords do not match. Please enter again.\n";
            continue;
        }
    
        break; 
    
    } while (true);

    file << newUser.nameandsur << "|" << newUser.phone << "|" << newUser.password << endl;
    ofstream courseFile(newUser.phone + ".txt"); courseFile.close();
    cout << "\nRegistration successful!"<<endl;
    cout << "Press Enter for next function ";
    tcflush(STDIN_FILENO, TCIFLUSH);

while (true) {
    char input = getchar();
    if (input == '\n') {
        clearScreen();
        break;
    } else {
        while (getchar() != '\n');
        cout << "❌ Invalid input. Please press Enter only.\n";
    }
}
}

bool LoginSystem::loginUser(User& currentUser) {
    ifstream file("user.txt");
    if (!file) {
        cout << "Cannot open user database.\n";
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
            //cout << "\nLogin Successful! Welcome " << user.nameandsur << endl;
            //saveLogin(currentUser);
            return true;
        }
    }

    cout << "Phone number or password incorrect.\n";
    return false;
}
