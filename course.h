#include  <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
#ifndef COURSE_H
#define COURSE_H


struct expiration_date{
    int d=0, m=0, y=0;
};
typedef struct expiration_date EXP;


class Course{
private:
    int course_id;
    EXP exp;
protected:
    float hours;
    string name;
public:
    Course(int id=0, string n="", float hrs=0, EXP ex = EXP());
    ~Course();
    //void print_course();
    void input_course();
    void save_to_file(const string& filename = "course.txt") const;
    static void load_from_file(const string& filename = "course.txt");
};
typedef Course* CoursePtr;


//add course constructor
Course::Course(int id, string n, float hrs, EXP ex){
    course_id = id;
    name = n;
    hours = hrs;
    exp = ex; 
    //next = NULL;
    //cout<< "Adding course " << name << endl;
}

//delete course //o~ <--me 4 hours old 
Course::~Course(){
    //cout <<"Deleting course : " << name << endl;
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

/*
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
*/

void Course::save_to_file(const string& filename) const {
    ofstream fout(filename, ios::app);
    if (!fout) {
        cout << "cannot open file" << endl;
        return;
    }

    fout << course_id << ","
         << name << ","
         << hours << ","
         << exp.d << "," << exp.m << "," << exp.y << endl;

    fout.close();
    cout << "successfully saved in " << filename << endl;
}

void Course::load_from_file(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "File not found: " << filename << endl;
        return;
    }

    string line;
    cout << "\n Courses from " << filename << ":\n";
    while (getline(fin, line)) {
        stringstream ss(line);
        string token, name;
        int id, d, m, y;
        float hrs;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ','); hrs = stof(token);
        getline(ss, token, ','); d = stoi(token);
        getline(ss, token, ','); m = stoi(token);
        getline(ss, token, ','); y = stoi(token);

        cout << "----------------------------\n";
        cout << "ID    : " << id << endl;
        cout << "Name  : " << name << endl;
        cout << "Hours : " << hrs << endl;
        cout << "Expiration Date : " << setfill('0') << setw(2) << d << "/"
             << setw(2) << m << "/" << y << endl;
    }

    fin.close();
}

#endif