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
    fout << course_id << "," << name << "," << hours << "," << hours << ","  // total, remaining
         << exp.d << "," << exp.m << "," << exp.y << endl;
    fout.close();
}



void Course::display(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "\n❌ Course file not found.\n";
        return;
    }

    string line;
    bool hasCourse = false;

    while (getline(fin, line)) {
        hasCourse = true;  // ถ้ามีบรรทัดอย่างน้อย 1 บรรทัด

        stringstream ss(line);
        int id, d, m, y;
        float total, remaining;
        string name, token;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ','); total = stof(token);
        getline(ss, token, ','); remaining = stof(token);
        getline(ss, token, ','); d = stoi(token);
        getline(ss, token, ','); m = stoi(token);
        getline(ss, token, ','); y = stoi(token);

        float completed = total - remaining;

        cout << "----------------------------" << endl
             << "ID            : " << id << endl
             << "Name          : " << name << endl
             << "Total Hours   : " << total << endl
             << "Completed     : " << completed << endl
             << "Remaining     : " << remaining << endl
             << "Expiration    : " << setfill('0') << setw(2) << d << "/"
                                << setw(2) << m << "/" << y << endl;
    }

    fin.close();

    if (!hasCourse) {
        cout << "\n Course Empty!\n ";
    }
}


void Course::delete_course_by_id(const string& filename, int targetID) {
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
    bool found = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        int id;
        string token;
        getline(ss, token, ','); id = stoi(token);

        if (id == targetID) {
            found = true; 
            continue;
        }

        fout << line << endl;
    }

    fin.close();
    fout.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (found)
        cout << "Course ID " << targetID << " deleted successfully.\n";
    else
        cout << "Course ID not found.\n";
}

