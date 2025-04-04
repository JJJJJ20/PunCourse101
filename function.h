#include<iostream>
using namespace std;

#include "course.h"
#include "login.h"
bool login();
void menu(const User& currentUser);


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


void menu(const User& currentUser){
    Course A;
    Progress P;
    int choice,selected_id;
    while(1){
    cout<<"Choose a number"<<endl
        <<"1. View course"<<endl
        <<"2. Update course progress"<<endl
        <<"3. Add course"<<endl
        <<"4. Exit"<<endl
        <<"Enter your number: ";
    cin>>choice;
    
        if (choice == 1) {
            //A.print_course();
            A.load_from_file(currentUser.phone + ".txt"); 
            cout<<"-----------"<<endl;
        } else if (choice == 2) {
            selected_id = P.choose_course(currentUser.phone + ".txt");
            P.update_progress(currentUser.phone + ".txt", selected_id);
            //P.print();

        } else if(choice==3){
            A.input_course();
            A.save_to_file(currentUser.phone + ".txt"); 
            cout<<"\n-----------";
        }else if (choice == 4) {
            cout << "ByeBye jubjub!\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }

    }
   // return a;
}