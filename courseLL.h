#include "course.h"
#ifndef COURSELL_H
#define COURSELL_H


struct CourseNode {
    Course* course;
    CourseNode* next;
    CourseNode(Course* c) : course(c), next(nullptr) {}
};

CourseNode* load_courses_into_list(const string& filename);
void delete_course_list(CourseNode* head);


#endif