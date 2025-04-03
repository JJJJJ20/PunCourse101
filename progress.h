#include  <iostream>
#include <iomanip>
#include <string>
using namespace std;

//cop jak chatGPT
class Progress {
private:
    Course* course;
    float completed_hours;
    float score;
public:
    Progress(Course* c = nullptr, float comp = 0.0f, float s = 0.0f);
    ~Progress();
    float get_progress_percent();
    void print();
};

//add course constructor
Progress::Progress(Course* c , float comp, float s){
    
    cout<< "Adding Progress " << name << endl;
}

//delete course //o~ <--me 4 hours old 
Progress::~Progress(){
    cout <<"Deleting Progress : " << name << endl;
}

float Progress::get_progress_percent() {
    return (completed_hours / course->hours) * 100.0f;
}

void Progress::print() {
    cout << "Course: " << course->name
         << ", Completed: " << completed_hours << "/" << course->total_hours
         << ", Progress: " << get_progress_percent() << "%"
         << ", Score: " << score << endl;
}