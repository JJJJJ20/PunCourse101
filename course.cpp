#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "course.h"
#include "courseLL.h"  


Course::Course(int id, string n, float hrs, EXP ex){
    course_id = id;
    name = n;
    hours = hrs;
    exp = ex; 
}

void Course::input_course(){
    cout << "Enter course ID: ";
    while (!(cin >> course_id)) {
        cin.clear(); // clear error flags
        cin.ignore(10000, '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number for course ID: ";
    }
    cin.ignore();  

    cout << "Enter course name: ";
    getline(cin, name);  // Get full name (including spaces)

    cout << "Enter course hours: ";
    while (!(cin >> hours)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a number for hours: ";
    }

    cout << "Enter expiration date (D M Y): ";
    while (!(cin >> exp.d >> exp.m >> exp.y)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid date. Enter expiration date (D M Y): ";
    }

}

void Course::save_to_file(const string& filename) const {
    ofstream fout(filename, ios::app);
    if (!fout) {
        cout << "Cannot open file.\n";
        return;
    }
    fout << course_id << "," << name << "," << hours << ","
         << exp.d << "," << exp.m << "," << exp.y << endl;
    fout.close();
}


void Course::display(const string& filename) {
    CourseNode* head = load_courses_into_list(filename);
    if (!head) {
        cout << "\nCourse Empty! Please add course first\n\n";
        return;
    }

    CourseNode* current = head;
    int d,m,y;
    while (current) {
        EXP exp;
        d = current->course->exp.d;
        m = current->course->exp.m;
        y = current->course->exp.y;
        cout << "----------------------------" << endl
             << "ID    : " << current->course->course_id << endl
             << "Name  : " << current->course->name << endl
             << "Hours : " << current->course->hours << endl
             << "Expiration Date : " << setfill('0') << setw(2) << d << "/"
             << setw(2) << m << "/" << y << endl;
        current = current->next;
    }

    delete_course_list(head);
}

