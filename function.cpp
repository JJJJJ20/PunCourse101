#include<iostream>
#include <algorithm>
using namespace std;
#include "function.h"
#include "login.h"


bool login() {
    User currentUser;
    LoginSystem auth;  // ✅ เพิ่มบรรทัดนี้

    cout << "Welcome!\n";
    
    int choice;
    do {
        cout << "==== Main Menu ====\n"
             << "1. Login\n"
             << "2. Register\n"
             << "3. Exit\n"
             << "Enter choice: ";
        cin >> choice;
        cin.ignore(); 

        if (choice == 1) {
            bool success = false;
            do {
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
            auth.registerUser(currentUser);  // ✅ และตรงนี้
        } else if (choice == 3) {
            cout << "ByeBye jubjub!\n";
            return false;    
        } else {
            cout << "Invalid choice. Try again.\n";
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
    int choice,inputID_progress,inputID_delete;
    CourseNode* head = nullptr;

    while(1){
    cout<<"Choose a number"<<endl
        <<"1. View course"<<endl
        <<"2. Update course progress"<<endl
        <<"3. Add course"<<endl
        <<"4. Delete course"<<endl
        <<"5. Edit course"<<endl
        <<"6. Exit"<<endl
        <<"Enter your number: ";
    cin>>choice;
    
        if (choice == 1) {
            if (head) delete_course_list(head);
            head = load_courses_into_list(filename + ".txt");
            A.display(head);
            cout << "----------------------------" << endl;
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