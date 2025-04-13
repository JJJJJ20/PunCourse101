#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "course.h"
#include "courseLL.h"  


Course::Course(int id, string n, float hrs,float rem, EXP ex){
    course_id = id;
    name = n;
    hours = hrs;
    remaining = rem;
    exp = ex; 
}

void Course::add_course(CourseNode* head){
    int inputID;
    bool existedID = false;

    do{
        existedID = false;
        cout << "Enter course ID: ";
        while (!(cin >> course_id)) {
            cin.clear(); // clear error flags
            cin.ignore(10000, '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number for course ID: ";
        }

        CourseNode* current=head;
        while (current) {
            if(current->course->getID() == course_id) {
                cout << "This ID already exists. Please enter a different ID.\n";
                existedID = true;
                break;
            }
            current = current -> next;
        }

    } while(existedID);


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
    fout << course_id << "," << name << "," << hours << "," << hours << ","
         << exp.d << "," << exp.m << "," << exp.y << endl;
    fout.close();
}



void Course::display(CourseNode* head) {
    if (!head) {
        cout << "\n Course file not found\n";
        return;
    }

    CourseNode* current = head;
    bool hasCourse = false;

    while (current) {
        hasCourse = true;

        int id = current->course->getID();
        string name = current->course->getName();
        float remaining = current->course->getRemaining();   
        float total = current->course->getHours(); 
        EXP exp = current->course->exp;

        float completed = total - remaining;

        cout << "----------------------------" << endl
             << "ID            : " << id << endl
             << "Name          : " << name << endl
             << "Total Hours   : " << total << endl
             << "Completed     : " << completed << endl
             << "Hours Left    : " << remaining << endl
             << "Expiration    : " << setfill('0') << setw(2) << exp.d << "/"
                                << setw(2) << exp.m << "/" << exp.y << endl;

        current = current->next;
    }

    if (!hasCourse) {
        cout << "\n Course Empty! \n";
    }
}


void Course::delete_course(const string& filename, int targetID) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Cannot open file.\n";
        return;
    }

    ofstream fout("temp.txt");
    if (!fout) {
        cout << "Cannot create temp file.\n";
        fin.close();
        return;
    }

    string line;
    //bool found = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        int id;
        string token;
        getline(ss, token, ','); id = stoi(token);

        if (id != targetID) {
            fout << line << endl;
        }
    }

    fin.close();
    fout.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    cout << "Course ID " << targetID << " deleted successfully.\n\n";

}

