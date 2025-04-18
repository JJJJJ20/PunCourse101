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
    return phone.length() == 10 && phone[0] == '0' && all_of(phone.begin(), phone.end(), ::isdigit);
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

/*
void LoginSystem::saveLogin(const User& currentUser) {
    ofstream file("logindata.txt");
    if (file)
        file << currentUser.nameandsur << "|" << currentUser.phone << "|" << currentUser.password << endl;
} */

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

    int back;
    bool isDuplicate;
    do {
        cout << "Enter your phone number (10 digits): ";
        getline(cin, newUser.phone);

        if (!isPhoneValid(newUser.phone)) {
            cout << "Invalid phone number.\n";
            do {
                cout << "Enter your choice (1 to continue, 2 to exit): ";
                cin >> back; cin.ignore();
                if (back == 2) return;
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
                cout << "Phone already registered.\n";
                do {
                    cout << "Enter your choice (1 to continue, 2 to exit): ";
                    cin >> back; cin.ignore();
                    if (back == 2) return;
                } while (back != 1);
                break;
            }
        }
    } while (isDuplicate);

    string confirmPass;
    do {
        cout << "Enter your password: ";
        getMaskedPassword(newUser.password, 20);
        if(newUser.password.length() < 8 ) cout<<"Your password must be at least 8 characters\n";
    } while (newUser.password.length() < 8 || newUser.password.find(' ') != string::npos);

    do {
        cout << "Confirm your password: ";
        getMaskedPassword(confirmPass, 20);
        if (confirmPass != newUser.password)
            cout << "Passwords do not match!\n";
    } while (confirmPass != newUser.password);

    file << newUser.nameandsur << "|" << newUser.phone << "|" << newUser.password << endl;
    ofstream courseFile(newUser.phone + ".txt"); courseFile.close();
    cout << "\nRegistration successful!\n";
    waitForEnter();
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
