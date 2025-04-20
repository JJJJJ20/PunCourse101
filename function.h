#include<iostream>
#include <functional>
using namespace std;

#include "course.h"
#include "login.h"
#include "courseLL.h"
#include "progress.h"

void menu(const User& currentUser);
bool login();
int choose_course(CourseNode* head);
int getValidatedInt(int min, int max, const string& prompt, function<void()> showMenu);
void showLoginMenu();
void printBunny(int position);
void runBunny(int steps, int delay_ms );