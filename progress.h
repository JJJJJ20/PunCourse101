#ifndef PROGRESS_H
#define PROGRESS_H

#include <iostream>
#include <string>
#include "course.h"
#include "courseLL.h"

using namespace std;

class Progress : public Course {
private:
    float completed_hours;
protected:
    Course* course;
public:
    Progress(Course* c = nullptr, float comp = 0.0f);
    ~Progress() {};

    //int choose_course(CourseNode* head);                        
    void update_progress(const string& filename, int ID);    
    void print(); 
    void decrease_course_hours(const string& filename, int id, float decrease);                                        
};

#endif
