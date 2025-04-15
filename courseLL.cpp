#include "courseLL.h"

#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;


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
        float hrs,remaining;
        string name, token;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ','); hrs = stof(token);
        getline(ss, token, ','); remaining = stof(token);
        getline(ss, token, ','); d = stoi(token);
        getline(ss, token, ','); m = stoi(token);
        getline(ss, token, ','); y = stoi(token);

        Course* c = create_course_from_data(id, name, hrs, remaining, {d, m, y});
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

CourseNode* sort_course_list_by_id(CourseNode* head) {
    CourseNode* sorted = nullptr;

    while (head) {
        CourseNode* current = head;
        head = head->next;
        current->next = nullptr;

        if (!sorted || current->course->getID() < sorted->course->getID()) {
            current->next = sorted;
            sorted = current;
        } else {
            CourseNode* temp = sorted;
            while (temp->next && temp->next->course->getID() < current->course->getID()) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    return sorted;
}


CourseNode* clone_course_list(CourseNode* head) {
    CourseNode* newHead = nullptr, *tail = nullptr;
    while (head) {
        Course* copiedCourse = create_course_from_data(
            head->course->getID(),
            head->course->getName(),
            head->course->getHours(),
            head->course->getRemaining(),
            head->course->getExpiration()
        );
        CourseNode* newNode = new CourseNode(copiedCourse);
        if (!newHead) newHead = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
        head = head->next;
    }
    return newHead;
}

Course* create_course_from_data(int id, string name, float hrs, float rem, EXP exp) {
    if (hrs <= 200) return new BasicCourse(id, name, hrs, rem, exp);
    else return new AdvancedCourse(id, name, hrs, rem, exp);
}

