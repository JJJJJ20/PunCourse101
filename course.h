#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

struct expiration_date {
    int d = 0, m = 0, y = 0;
};
typedef struct expiration_date EXP;

struct CourseNode;

class Course {
protected:
    float hours, remaining;
    string name;
    int course_id;
    EXP exp;
public:
    Course(int id = 0, string n = "", float hrs = 0, float rem = 0, EXP ex = EXP());
    virtual ~Course() {}

    virtual void display_info() const;
    virtual string getType() const { return "Generic"; }

    int getID() const { return course_id; }
    string getName() const { return name; }
    float getHours() const { return hours; }
    float getRemaining() const { return remaining; }
    EXP getExpiration() const { return exp; }

    void display(CourseNode* head);
    void add_course(CourseNode* head);
    void save_to_file(const string& filename = "course.txt") const;
    static void load_from_file(const string& filename = "course.txt");
    static void delete_course(const string& filename, int targetID);
    static void edit_course(const string& filename, int targetID);
};

class BasicCourse : public Course {
public:
    BasicCourse(int id, string n, float hrs, float rem, EXP ex) : Course(id, n, hrs, rem, ex) {}
    void display_info() const override;
    string getType() const override { return "Basic"; }
};

class AdvancedCourse : public Course {
public:
    AdvancedCourse(int id, string n, float hrs, float rem, EXP ex) : Course(id, n, hrs, rem, ex) {}
    void display_info() const override;
    string getType() const override { return "Advanced"; }
};


#endif