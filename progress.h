#include  <iostream>
#include <iomanip>
#include <string>
#include "course.h"
#include "courseLL.h"
#ifndef PROGRESS_H
#define PROGRESS_H
using namespace std;

//cop jak chatGPT
class Progress:public Course{
private:
    float completed_hours;
protected:
    Course* course;
public:
    Progress(Course* c = nullptr, float comp = 0.0f);
    ~Progress() {};
    int choose_course(CourseNode* head);
    void update_progress(const string& filename, int ID);
    void print();
};

//add course constructor
Progress::Progress(Course* c , float comp): course(c), completed_hours(comp) {
    if (course)
    cout<< "Adding Progress " << Course::name << endl;
}


void Progress::print() {
    if (!course) {
        cout << "No course information.\n";
        return;
    }
    cout << "Course: " << Course::name
         << ", Completed: " << completed_hours << "/" << Course::hours
         << endl;
}


int Progress::choose_course(CourseNode* head) {
    if (!head) {
        cout << "\nNo courses available.\n";
        return -1;
    }

    cout << "\n All Courses:\n";

    CourseNode* current = head;
    while (current) {
        cout << current->course->getID() << "  " << current->course->getName() << endl;
        current = current->next;
    }

    int inputID;
    cout << "\nEnter the course ID to update progress: ";
    cin >> inputID;

    return inputID;
}



void Progress::update_progress(const string& filename, int ID){
    ifstream fin(filename);
    if (!fin) {
        cout << "\n Cannot open file: " << filename << endl;
    }
    string line;
    CoursePtr selectedCourse = nullptr;
 
    while (getline(fin, line)) {
        stringstream ss(line);
        int id, d, m, y;
        float hrs;
        string name, token;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ','); hrs = stof(token);
        getline(ss, token, ','); d = stoi(token);
        getline(ss, token, ','); m = stoi(token);
        getline(ss, token, ','); y = stoi(token);

        if (id == ID) {
            selectedCourse = new Course(id, name, hrs, {d, m, y});
            break;
        }
    }

    fin.close();

    if (!selectedCourse) {
        cout << "\n Course not found\n";
        //return nullptr;
    }

    float done;
    cout << "Enter hours completed: ";
    cin >> done;

    Progress p(selectedCourse, done);
    p.print();

    delete selectedCourse;

   
}



#endif