#ifndef COURSELL_H
#define COURSELL_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include "course.h"



// ✅ CourseNode for Linked List
struct CourseNode {
    Course* course;
    CourseNode* next;
    CourseNode(Course* c) : course(c), next(nullptr) {}
};

// ✅ Head pointer to our linked list
CourseNode* load_courses_into_list(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Cannot open file: " << filename << endl;
        return nullptr;
    }

    CourseNode* head = nullptr;
    CourseNode* tail = nullptr;
    string line;

    while (getline(fin, line)) {
        stringstream ss(line);
        int id, d, m, y;
        float hrs;
        string name, token;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ','); hrs = stof(token);
        getline(ss, token, ','); d = stoi(token);
        getline(ss, token, ','); m = stoi(token);
        getline(ss, token, ','); y = stoi(token);

        Course* c = new Course(id, name, hrs, {d, m, y});
        CourseNode* node = new CourseNode(c);

        if (!head) head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
    }

    fin.close();
    return head;
}


/*
Course* choose_course(CourseNode* head) {
    if (!head) {
        cout << "No courses available." << endl;
        return nullptr;
    }

    cout << "\nAvailable Courses:\n";
    CourseNode* curr = head;
    while (curr) {
        cout << "ID: " << curr->course->getID()
             << " | Name: " << curr->course->getName() << endl;
        curr = curr->next;
    }

    int inputID;
    cout << "\nEnter course ID to update: ";
    cin >> inputID;

    curr = head;
    while (curr) {
        if (curr->course->getID() == inputID) return curr->course;
        curr = curr->next;
    }

    cout << "Course ID not found." << endl;
    return nullptr;
}
    */

// ✅ Cleanup
void delete_course_list(CourseNode* head) {
    while (head) {
        CourseNode* temp = head;
        head = head->next;
        delete temp->course;
        delete temp;
    }
}


#endif