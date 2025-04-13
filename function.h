#include<iostream>
using namespace std;

#include "course.h"
#include "login.h"
#include "courseLL.h"
#include "progress.h"
void menu(const User& currentUser);
bool login();
int choose_course(CourseNode* head);