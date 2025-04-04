#include  <iostream>
#include <iomanip>
#include <string>
#include "course.h"
using namespace std;

//cop jak chatGPT
class Progress:public Course{
private:
    float completed_hours;
    float score;
protected:
    Course* course;
public:
    Progress(Course* c = nullptr, float comp = 0.0f, float s = 0.0f);
    ~Progress();
    float get_progress_percent();
    void print();
};

//add course constructor
Progress::Progress(Course* c , float comp, float s): course(c), completed_hours(comp), score(s) {
    if (course)
    cout<< "Adding Progress " << Course::name << endl;
}

//delete course //o~ <--me 4 hours old 
Progress::~Progress(){
    //cout <<"Deleting Progress : " << Course::name << endl;
}

float Progress::get_progress_percent() {
    return (completed_hours / Course::hours) * 100.0f;
}

void Progress::print() {
    cout << "Course: " << Course::name
         << ", Completed: " << completed_hours << "/" << Course::hours
         << ", Progress: " << get_progress_percent() << "%"
         << ", Score: " << score << endl;
}