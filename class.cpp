#include  <iostream>
#include <iomanip>
#include <string>
using namespace std;
#include "class.h"

//add course constructor
Course::Course(int id, string n, float hrs, EXP ex){
    course_id = id;
    name = n;
    hours = hrs;
    exp = ex; 
    //next = NULL;
    cout<< "Adding course " << name << endl;
}

//delete course //o~ <--me 4 hours old 
Course::~Course(){
    cout <<"Deleting course : " << name << endl;
}



//rub input from user, return pen course
//Course input_course(){ //อันนี้ if ไม่ให้input_course เป็นmemberของclass มนจต่างกันไงกับทำในmain

void Course::input_course(){
    cout << "Enter course ID: ";
    cin >> course_id;
    cin.ignore();  // Ignore newline character left in buffer

    cout << "Enter course name: ";
    getline(cin, name);  // Get full name (including spaces)

    cout << "Enter course hours: ";
    cin >> hours;

    cout << "Enter expiration date (D M Y): ";
    cin >> exp.d >> exp.m >> exp.y;

}


void Course::print_course(){
    cout<<"Course A -------------------"<<endl
        <<"ID    : " << course_id << endl
        <<"Name  : " << name << endl
        <<"Hours : " << hours << endl
        <<"Hours (left) : " << '2' << endl //idk how tong rub input progress a
        <<"Expiration Date : "  << setfill('0')<<setw(2) << exp.d << "/"
                                << setfill('0')<<setw(2) << exp.m << "/"
                                << setfill('0')<<setw(2) << exp.y << endl;
}