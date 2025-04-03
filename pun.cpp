#include<iostream>
using namespace std;

#include "course.h"
#include "progress.h"
#include "login.h"
int login();
void menu();


int login(){
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
            loginUser(currentUser);
            return 1; 
            break;
        } else if (choice == 2) {
            registerUser(currentUser);
        } else if (choice == 3) {
            cout << "Goodbye!\n";
            return 0;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (true);

    return 0;
}

int main(int argc, char *argv[]){
 if(login()){

    menu();
   
 }
}

void menu(){
    Course A;
    Progress P;
    int choice;
    while(1){
    cout<<"Choose a number"<<endl
        <<"1. View course"<<endl
        <<"2. Update course progress"<<endl
        <<"3. Add course"<<endl
        <<"4. Exit"<<endl
        <<"Enter your number: ";
    cin>>choice;
    
        if (choice == 1) {
            A.print_course();
            cout<<"-----------"<<endl;
        } else if (choice == 2) {
           P.print();

        } else if(choice==3){
            A.input_course();
            cout<<"\n-----------";
        }else if (choice == 4) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }

    }
   // return a;
}