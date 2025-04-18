#include<iostream>
#include <algorithm>
#include <filesystem>
using namespace std;
#include "function.h"
#include "login.h"

LoginSystem auth;

bool login() {
    User currentUser;

    system("clear");
    
    int choice;
    do {
        cout << "╔════════════════════════════════════╗\n";
        cout << "║     🎓 Welcome to Puncourse101     ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║ 1. 🔐 Login                        ║\n";
        cout << "║ 2. 📝 Register                     ║\n";
        cout << "║ 3. 🚪 Exit                         ║\n";
        cout << "╚════════════════════════════════════╝\n";
        cout << "👉 Enter choice: ";
        cin >> choice;
        cin.ignore(); 

        if (choice == 1) {
            bool success = false;
            do {
                system("clear");
                cout << "🔓 Logging in...\n";
                success = auth.loginUser(currentUser);  // ✅ เปลี่ยนตรงนี้
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
    return inputID;
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

    while(1){
        system("clear");
        if (head) delete_course_list(head); 
        head = load_courses_into_list(filename + ".txt");
        bool hasCourse = (head != nullptr);

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
            cout <<"║"<< "\033[90m 1. 📚 View all courses                     \033[0m"<<"║"<<endl;
            cout << "║"<<"\033[90m 2. ⏱️  Update course progress               \033[0m"<<"║"<<endl;
            cout << "║ 3. ➕ Add new course                       ║\n";
            cout << "║"<<"\033[90m 4. ❌ Delete a course                      \033[0m"<<"║"<<endl;
            cout << "║"<<"\033[90m 5. ✏️  Edit course details                  \033[0m"<<"║"<<endl;
        }

        cout << "║ 6. 🚪 Exit to main menu                    ║\n";
        cout << "╚════════════════════════════════════════════╝\n";
        cout << "👉 Enter your number: ";
        cin >> choice;

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
            if (!head) {
                continue;
            }
            inputID_progress = choose_course(head);
            P.update_progress(filename + ".txt", inputID_progress);
            //sys.waitForEnter();
        } else if(choice==3){
            A.add_course(head);
            A.save_to_file(currentUser.phone + ".txt"); 
            cout << "\n----------------------------" << endl;
        }else if (choice == 4) {
            if (head) delete_course_list(head);
            head = load_courses_into_list(filename + ".txt"); 
            if (!head) {
                continue;
            }
            inputID_progress = choose_course(head);
            A.delete_course(currentUser.phone + ".txt", inputID_progress);

        }else if (choice == 5) {
            if (head) delete_course_list(head);
            head = load_courses_into_list(filename + ".txt");
            if (!head) {
                continue;
            }
            inputID_progress = choose_course(head);
            A.edit_course(currentUser.phone + ".txt", inputID_progress);
        }else if (choice == 6) {
                cout << "👋ByeBye jubjub!\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
 

}