#include<iostream>
#include <algorithm>
using namespace std;
#include "function.h"
#include "login.h"


bool login() {
    User currentUser;
    LoginSystem auth;  // ✅ เพิ่มบรรทัดนี้

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
            auth.registerUser(currentUser);  // ✅ และตรงนี้
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

    CourseNode* cloned = clone_course_list(head);
    CourseNode* sorted = sort_course_list_by_id(cloned);

    cout << "\n All Courses:\n";

    CourseNode* current = sorted;
    while (current) {
        cout << current->course-> getID() << "  " << current->course->getName() << endl;
        current = current->next;
    }

    int inputID;
    cout << "\nEnter the course ID: ";
    cin >> inputID;

    return inputID;
}


void menu(const User& currentUser){
    Course A;
    Progress P;
    string filename = currentUser.phone;
    string name = currentUser.nameandsur;
    int choice,inputID_progress,inputID_delete;
    CourseNode* head = nullptr;

    string short_name = name.substr(0, min((size_t)18, name.size()));

    while(1){
        system("clear");
        cout << "╔════════════════════════════════════════════╗\n";
        cout << "║ 🎉 Login Successful! Welcome " << short_name;
        for (int i = short_name.length(); i < 14; ++i) cout << " ";
        cout << "║\n"
        << "╠════════════════════════════════════════════╣\n"
        << "║ 1. 📚 View all courses                     ║\n"
        << "║ 2. ⏱️  Update course progress               ║\n"
        << "║ 3. ➕ Add new course                       ║\n"
        << "║ 4. ❌ Delete a course                      ║\n"
        << "║ 5. ✏️  Edit course details                  ║\n"
        << "║ 6. 🚪 Exit to main menu                    ║\n"
        << "╚════════════════════════════════════════════╝\n"
        << "👉 Enter your number: ";
        cin>>choice;
        cin.ignore();

        system("clear");
        if (choice == 1) {
            if (head) delete_course_list(head);
            head = load_courses_into_list(filename + ".txt");
            A.display(head);
        } else if (choice == 2) {
            if (head) delete_course_list(head);
            head = load_courses_into_list(filename + ".txt");
            if (!head) {
                cout << "\nNo courses found\n\n";
                continue;
            }
            inputID_progress = choose_course(head);
            P.update_progress(filename + ".txt", inputID_progress);
        
        } else if(choice==3){
            A.add_course(head);
            A.save_to_file(currentUser.phone + ".txt"); 
            cout << "\n----------------------------" << endl;
        }else if (choice == 4) {
            if (head) delete_course_list(head);
            head = load_courses_into_list(filename + ".txt"); 
            if (!head) {
                cout << "\nNo courses found\n\n";
                continue;
            }
            inputID_progress = choose_course(head);
            A.delete_course(currentUser.phone + ".txt", inputID_progress);

        }else if (choice == 5) {
            if (head) delete_course_list(head);
            head = load_courses_into_list(filename + ".txt");
            if (!head) {
                cout << "\nNo courses found\n\n";
                continue;
            }
            inputID_progress = choose_course(head);
            A.edit_course(currentUser.phone + ".txt", inputID_progress);
        }else if (choice == 6) {
                cout << "ByeBye jubjub!\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }


}