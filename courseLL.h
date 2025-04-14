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
CourseNode* sort_course_list_by_id(CourseNode* head);
CourseNode* clone_course_list(CourseNode* head);


#endif