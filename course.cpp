#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
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

extern LoginSystem auth;

void Course::display_info() const {
    float completed = hours - remaining;
    float percent = (hours > 0) ? (completed / hours) * 100 : 0;
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
         while (true) {
            cout << "Enter course ID: ";
            cin >> course_id;

            if (cin.fail()) {
                cin.clear(); 
                cin.ignore(10000, '\n'); 
                cout << "Invalid input. Please enter only numbers for course ID" << endl;
             } else if (course_id < 0) {
                cout << "Invalid input. Please enter counting number only for course ID" << endl;
             } 
             else break;  
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

    while(true) {
        cout << "Enter course hours: ";
        cin >> hours;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number for hours"<< endl;
        } else if (hours < 1) {
            cout << "Please enter positive numbers only." << endl;
        } else {
            cin.ignore(10000, '\n');
            break;
        }
    }


    while(true) {
        cout << "Enter expiration date (D M Y): ";
        cin >> exp.d >> exp.m >> exp.y;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(10000, '\n'); 
             cout << "Invalid input. Please enter only numbers\n";
         } else if (exp.d < 1 || exp.d > 31) {
                cout << "Invalid date. Day must be between 1 and 31\n"; }  
            else if (exp.m < 1 || exp.m > 12) {
                cout << "Invalid month. Month must be between 1 and 12\n"; }  
            else if (exp.y < 2025 || exp.y > 2570) {
                cout << "Invalid year. Year must be between 2025 and 2570\n"; }  
            else break; 
        
    };

    remaining = hours;
    cout << endl;
    auth.waitForEnter();
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
    if (!head) {
        return;
    }

    CourseNode* sorted = sort_course_list_by_id(head);
    CourseNode* current = sorted;

    while (current) {
        current->course->display_info();
        current = current->next;
    }
    
    delete_course_list(sorted);

    string dummy;
    cout << "Press Enter for next function ";
    getline(cin, dummy);
    system("clear");
}


void Course::delete_course(const string& filename, int targetID) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Cannot open file."<<endl;
        auth.waitForEnter();
        return;
    }

    ofstream fout("temp.txt");
    if (!fout) {
        cout << "Cannot create temp file."<<endl;
        fin.close();
        auth.waitForEnter();
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
        cout << "Course ID " << targetID << " not found.\n"<<endl;
        remove("temp.txt");
        auth.waitForEnter();
        return;
    }

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    cout << "Course ID " << targetID << " deleted successfully.\n"<<endl;
    auth.waitForEnter();

}

void Course::edit_course(const string& filename, int targetID) {
    ifstream fin(filename);
    ofstream fout("temp.txt");
    if (!fin || !fout) {
        cout << "Error opening file.\n";
        auth.waitForEnter();
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

            while(true) {
                cout << "Enter expiration date (D M Y): ";
                cin >> d >> m >> y;
                //cin.ignore(10000, '\n');
        
                if (cin.fail()) {
                    cin.clear(); 
                    cin.ignore(10000, '\n'); 
                     cout << "Invalid input. Please enter only numbers"<<endl;
                 } else if (d < 1 || d > 31) {
                        cout << "Invalid date. Day must be between 1 and 31"<<endl; }  
                    else if (m < 1 || m > 12) {
                        cout << "Invalid month. Month must be between 1 and 12"<<endl; }  
                    else if (y < 2000 || y > 2570) {
                        cout << "Invalid year. Year must be between 2000 and 2570"<<endl; }  
                    else {
                        break;
                    } 
                
            };
            remaining = total;
            cout << "\n✅ Course updated successfully."<<endl;
            auth.waitForEnter();
        }

        fout << id << "," << name << "," << total << "," << remaining << ","
             << d << "," << m << "," << y << endl;

    }

    fin.close();
    fout.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (!found) {
        cout << "Course ID not found."<<endl;
        auth.waitForEnter();
        return ;
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
