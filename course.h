#include  <iostream>
#include <iomanip>
#include <string>
#include <fstream>




using namespace std;

#ifndef COURSE_H
#define COURSE_H

struct CourseNode;

struct expiration_date{
    int d=0, m=0, y=0;
};
typedef struct expiration_date EXP;


class Course{
    friend struct CourseNode;
private:
protected:
    float hours;
    string name;
    int course_id;
    EXP exp;
public:
    Course(int id=0, string n="", float hrs=0, EXP ex = EXP());
    ~Course() {};
    static void display(const string& filename);
    void input_course();
    void save_to_file(const string& filename = "course.txt") const;
    static void load_from_file(const string& filename = "course.txt");
    int getID() const { return course_id; }
    string getName() const { return name; }
};
typedef Course* CoursePtr;





#endif