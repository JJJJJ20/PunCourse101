#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "course.h"
#include "courseLL.h"  
#include "login.h"


Course::Course(int id, string n, float hrs,float rem, EXP ex){
    course_id = id;
    name = n;
    hours = hrs;
    remaining = rem;
    exp = ex; 
}


void Course::display_info() const {
    float completed = hours - remaining;
    float percent = (hours > 0) ? (completed / hours) * 100 : 0;

    // Progress bar with █ and ░
    int barWidth = 20;
    int filled = static_cast<int>((percent / 100.0) * barWidth);
    string progressBar = "[" + string(filled, '#') + string(barWidth - filled, '-') + "]";

    cout << "═════════════════════════════════════════════"<<endl
    << "🆔 Course ID   : " << course_id << endl
    << "📚 Name        : " << name << endl
    << fixed << setprecision(2)
    << "📘 Course Type : " << getType() << endl
    << "🕒 Total Hours : " << hours << endl
    << "✅ Completed   : " << completed << " (" << percent << "%)"<<endl
    << "📊 Progress    : " << progressBar << endl
    << "⏳ Hours Left  : " << remaining << endl
    << "📅 Expiration  : "
         << setfill('0') << setw(2) << exp.d << "/"
         << setw(2) << exp.m << "/" << exp.y << endl
    << "═════════════════════════════════════════════\n\n";
}


void BasicCourse::display_info() const {
    Course::display_info();
}

void AdvancedCourse::display_info() const {
    Course::display_info();
}


void Course::add_course(CourseNode* head){
    //int inputID;
    bool existedID = false;

    do{
        existedID = false;
        cout << "Enter course ID: ";
        while (!(cin >> course_id)) {
            cin.clear(); // clear error flags
            cin.ignore(10000, '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number for course ID: ";
        }

        CourseNode* current=head;
        while (current) {
            if(current->course->getID() == course_id) {
                cout << "This ID already exists. Please enter a different ID.\n";
                existedID = true;
                break;
            }
            current = current -> next;
        }

    } while(existedID);


    cin.ignore();  

    cout << "Enter course name: ";
    getline(cin, name);

    cout << "Enter course hours: ";
    while (!(cin >> hours)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a number for hours: ";
    }

    cout << "Enter expiration date (D M Y): ";
    while (!(cin >> exp.d >> exp.m >> exp.y)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid date. Enter expiration date (D M Y): ";
    }

    remaining = hours;
}

void Course::save_to_file(const string& filename) const {
    ofstream fout(filename, ios::app);
    if (!fout) {
        cout << "Cannot open file.\n";
        return;
    }
    fout << course_id << "," << name << "," << hours << "," << hours << ","
         << exp.d << "," << exp.m << "," << exp.y << endl;
    fout.close();
}



void Course::display(CourseNode* head) {
    extern LoginSystem auth;
    if (!head) {
        cout << "\nCourse file not found\n";
        auth.waitForEnter();
        return;
    }

    CourseNode* sorted = sort_course_list_by_id(head);
    //CourseNode* sorted = sort_course_list_by_id(clone);
    CourseNode* current = sorted;

    while (current) {
        current->course->display_info();
        current = current->next;
    }
    
    delete_course_list(sorted);
    auth.waitForEnter();
}


void Course::delete_course(const string& filename, int targetID) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Cannot open file.\n";
        return;
    }

    ofstream fout("temp.txt");
    if (!fout) {
        cout << "Cannot create temp file.\n";
        fin.close();
        return;
    }

    string line;
    bool found = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        int id;
        string token;
        getline(ss, token, ','); id = stoi(token);

        if (id != targetID) {
            fout << line << endl;
        }
        else {
            found = true;
        }
    }

    fin.close();
    fout.close();

    if (!found) {
        cout << "Course ID " << targetID << " not found.\n\n";
        remove("temp.txt");
        return;
    }

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    cout << "Course ID " << targetID << " deleted successfully.\n\n";

}

void Course::edit_course(const string& filename, int targetID) {
    ifstream fin(filename);
    ofstream fout("temp.txt");
    if (!fin || !fout) {
        cout << "Error opening file.\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        int id, d, m, y;
        float total, remaining;
        string name, token;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ','); total = stof(token);
        getline(ss, token, ','); remaining = stof(token);
        getline(ss, token, ','); d = stoi(token);
        getline(ss, token, ','); m = stoi(token);
        getline(ss, token, ','); y = stoi(token);

        if (id == targetID) {
            found = true;
            cout << "Editing course: " << name << endl;

            cout << "Enter new course name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter new total hours: ";
            while (!(cin >> total)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Enter a number: ";
            }

            cout << "Enter expiration date (D M Y): ";
            while (!(cin >> d >> m >> y)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Enter date (D M Y): ";
            }
            remaining = total;
        }

        fout << id << "," << name << "," << total << "," << remaining << ","
             << d << "," << m << "," << y << endl;
    }

    fin.close();
    fout.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (!found) {
        cout << "Course ID not found.\n";
    }
}

void Course::show_course_list(CourseNode* head) {
    if (!head) {
        cout << "No courses available.\n";
        return;
    }
    CourseNode* sorted = sort_course_list_by_id(clone_course_list(head));
    CourseNode* current = sorted;

    cout << "📚 Available Courses:\n";
    cout << "═══════════════════════════════════════════════════════\n";
    cout << "🆔 ID              📘 Course Name\n";
    cout << "───────────────────────────────────────────────────────\n";

    while (current) {
        int id = current->course->getID();
        string name = current->course->getName();

        if (name.length() > 30) name = name.substr(0, 27) + "...";

        stringstream row;
        row << id;
        int spaceID = 19 - to_string(id).length();
        row << string(spaceID, ' ') << " ";

        row << name;

        cout << row.str() << endl;
        current = current->next;
    }

    cout << "═══════════════════════════════════════════════════════\n";

    delete_course_list(sorted);
}
