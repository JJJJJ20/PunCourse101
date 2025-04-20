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
    void update_progress(const string& filename, int ID);                                    
};

#endif
