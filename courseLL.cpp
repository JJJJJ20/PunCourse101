#include "courseLL.h"

#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// ✅ Only define these ONCE in this file
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

void delete_course_list(CourseNode* head) {
    while (head) {
        CourseNode* temp = head;
        head = head->next;
        delete temp->course;
        delete temp;
    }
}
