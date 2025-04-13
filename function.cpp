#include<iostream>
using namespace std;
#include "function.h"


bool login() {
    User currentUser;

    cout << "Welcome!\n";
    
    int choice;
    do {
        cout << "==== Main Menu ====\n"
             << "1. Login\n"
             << "2. Register\n"
             << "3. Exit\n"
             << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // clear newline

        if (choice == 1) {
            bool success = false;
            do {
                success = loginUser(currentUser);  // เปลี่ยน loginUser ให้ return bool ด้วย
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
            registerUser(currentUser);
        } else if (choice == 3) {
            cout << "ByeBye jubjub!\n";
            return false;    
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}

int choose_course(CourseNode* head) {
    if (!head) {
        cout << "\nNo courses available.\n";
        return -1;
    }

    cout << "\n All Courses:\n";

    CourseNode* current = head;
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

    CourseNode* head;
    head = load_courses_into_list(filename);


    while(1){
    cout<<"Choose a number"<<endl
        <<"1. View course"<<endl
        <<"2. Update course progress"<<endl
        <<"3. Add course"<<endl
        <<"4. Delete course"<<endl
        <<"5. Exit"<<endl
        <<"Enter your number: ";
    cin>>choice;
    
        if (choice == 1) {
            //A.print_course();
            A.display(currentUser.phone + ".txt"); 
            cout<<"-----------"<<endl;
        } else if (choice == 2) {
            // โหลดใหม่ทุกครั้งก่อนอัปเดต
            delete_course_list(head); // ล้างอันเก่า (ถ้ามี)
            head = load_courses_into_list(filename + ".txt");
        
            if (!head) {
                cout << "No courses found.\n";
                continue;
            }
        
            inputID_progress = choose_course(head);
            P.update_progress(filename + ".txt", inputID_progress);
        
        } else if(choice==3){
            A.input_course();
            A.save_to_file(currentUser.phone + ".txt"); 
            cout<<"\n-----------";
        }else if (choice == 4) {
            /*int delID;
            cout << "Enter course ID to delete: ";
            cin >> delID;
            P.delete_course(currentUser.phone + ".txt", delID); */

            inputID_progress = choose_course(head);
            A.delete_course(currentUser.phone + ".txt", inputID_progress);
        }else if (choice == 5) {
                cout << "ByeBye jubjub!\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }

    }


}