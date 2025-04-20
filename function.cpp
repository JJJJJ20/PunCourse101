#include<iostream>
#include <algorithm>
#include <regex>
#include <filesystem>
using namespace std;
#include "function.h"
#include "login.h"

LoginSystem auth;


int getValidatedInt(int min, int max, const string& prompt, function<void()> showMenu) {
    string input;
    while (true) {
        cout << prompt;
        cin >> input;
        cin.ignore();

        // เช็คว่า input เป็นตัวเลขล้วน ไม่ใช่ float
        if (all_of(input.begin(), input.end(), ::isdigit)) {
            int value = stoi(input);
            if (value >= min && value <= max) {
                return value;
            } else {
                system("clear");
                showMenu();
                cout << "❌ Please enter a number between " << min << " and " << max << ".\n";
            }
        } else {
            system("clear");
            showMenu();
            cout << "❌ Invalid input. Please enter an integer number only.\n";
        }
    }
}

void showLoginMenu() {
        cout << "╔════════════════════════════════════╗\n";
        cout << "║     🎓 Welcome to Puncourse101     ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║ 1. 🔐 Login                        ║\n";
        cout << "║ 2. 📝 Register                     ║\n";
        cout << "║ 3. 🚪 Exit                         ║\n";
        cout << "╚════════════════════════════════════╝\n";
}
bool login() {
    User currentUser;

    system("clear");
    
    int choice;
    do {
        showLoginMenu();
        choice = getValidatedInt(1, 3, "👉 Enter choice (1-3): ", showLoginMenu);

        if (choice == 1) {
            bool success = false;
            do {
                system("clear");
                cout << "🔓 Logging in...\n";
                success = auth.loginUser(currentUser); 
                if (!success) {
                    string retry;
                    cout << "Do you want to try again? (y/n): ";
                    getline(cin, retry);
                    if (retry != "y" && retry != "Y") {
                        system("clear");
                        break;
                    }
                }
            } while (!success);

            if (success) {
                menu(currentUser); 
                return true;
            }
        } else if (choice == 2) {
            system("clear");
            cout << "✍️ Registering new user...\n";
            auth.registerUser(currentUser);  //  และตรงนี้
        } else if (choice == 3) {
            system("clear");
            cout << "👋ByeBye jubjub!\n";
            return false;    
        } else {
            system("clear");
        }
    } while (true);
}


int choose_course(CourseNode* head) {
    Course temp;
    temp.show_course_list(head);
    int inputID;
    cout << "🔎 Enter the course ID to select: ";
    cin >> inputID;
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return inputID;
}

void showMainMenu(const string& short_name, bool hasCourse) {
    cout << "╔════════════════════════════════════════════╗\n";
    cout << "║ 🎉 Login Successful! Welcome " << short_name;
    for (int i = short_name.length(); i < 14; ++i) cout << " ";
    cout << "║\n";
    cout << "╠════════════════════════════════════════════╣\n";

    if (hasCourse) {
        cout << "║ 1. 📚 View all courses                     ║\n";
        cout << "║ 2. ⏱️  Update course progress               ║\n";
        cout << "║ 3. ➕ Add new course                       ║\n";
        cout << "║ 4. ❌ Delete a course                      ║\n";
        cout << "║ 5. ✏️  Edit course details                  ║\n";
    } else {
        cout <<"║" << "\033[90m 1. 📚 View all courses                     \033[0m" << "║\n";
        cout <<"║" << "\033[90m 2. ⏱️  Update course progress               \033[0m" << "║\n";
        cout << "║ 3. ➕ Add new course                       ║\n";
        cout <<"║" << "\033[90m 4. ❌ Delete a course                      \033[0m" << "║\n";
        cout <<"║" << "\033[90m 5. ✏️  Edit course details                  \033[0m" << "║\n";
    }

    cout << "║ 6. 🚪 Exit to main menu                    ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
}

void menu(const User& currentUser){
    Course A;
    Progress P;
    LoginSystem sys;
    string filename = currentUser.phone;
    string name = currentUser.nameandsur;
    int choice,inputID_progress,inputID_delete;
    CourseNode* head = nullptr;

    string short_name = name.substr(0, min((size_t)14, name.size()));
    //system("clear");

    while (1) {
        system("clear");
        if (head) delete_course_list(head);
        head = load_courses_into_list(filename + ".txt");
        bool hasCourse = (head != nullptr);

    
        showMainMenu(short_name, hasCourse);

        int choice = getValidatedInt(1, 6, "👉 Enter your number (1–6): ", [&]() {
            showMainMenu(short_name, hasCourse);
        });

        system("clear");

        if (choice == 1) {
            if (head) delete_course_list(head);
            head = load_courses_into_list(filename + ".txt");
            CourseNode* clone = clone_course_list(head);
            A.display(clone);
            delete_course_list(clone);
        } else if (choice == 2) {
            if (head) delete_course_list(head);
            head = load_courses_into_list(filename + ".txt");
            if (!head) continue;
            int inputID_progress = choose_course(head);
            P.update_progress(filename + ".txt", inputID_progress);
        } else if (choice == 3) {
            A.add_course(head);
            A.save_to_file(currentUser.phone + ".txt");
        } else if (choice == 4) {
            if (head) delete_course_list(head);
            head = load_courses_into_list(filename + ".txt");
            if (!head) continue;
            int inputID_progress = choose_course(head);
            A.delete_course(currentUser.phone + ".txt", inputID_progress);
        } else if (choice == 5) {
            if (head) delete_course_list(head);
            head = load_courses_into_list(filename + ".txt");
            if (!head) continue;
            int inputID_progress = choose_course(head);
            A.edit_course(currentUser.phone + ".txt", inputID_progress);
        } else if (choice == 6) {
            cout << "👋ByeBye jubjub!\n";
            break;
        }
    }
}