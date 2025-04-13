#include "progress.h"
#include <fstream>
#include <sstream>

Progress::Progress(Course* c, float comp) : course(c), completed_hours(comp) {
    if (course)
        cout << "Adding Progress " << Course::name << endl;
}

void Progress::print() {
    if (!course) {
        cout << "No course information.\n";
        return;
    }

    cout << "Course: " << course->getName()
     << ", Completed: " << completed_hours << "/" << course->getHours()
     << " (" << (course->getHours() - completed_hours) << " hours left)"
     << endl;
}


void Progress::update_progress(const string& filename, int ID) {
    ifstream fin(filename);
    ofstream fout("temp.txt");
    if (!fin || !fout) {
        cout << "\n Error opening files.\n";
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

        if (id == ID) {
            found = true;
            float done;
            cout << "Enter hours completed: ";
            cin >> done;

            if (done > remaining) {
                cout << "You cannot complete more than remaining hours. Adjusted to maximum.\n";
                done = remaining;
            }

            remaining -= done;
            cout << "Updated: " << name << " -> Completed: " << total - remaining
                 << "/" << total << " (" << remaining << " hours left)\n";
        }

        // Write (whether updated or not)
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


void Progress::decrease_course_hours(const string& filename, int id, float decrease) {
    ifstream fin(filename);
    ofstream fout("temp.txt");
    string line;

    while (getline(fin, line)) {
        stringstream ss(line);
        int cid, d, m, y;
        float hrs;
        string name, token;

        getline(ss, token, ','); cid = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ','); hrs = stof(token);
        getline(ss, token, ','); d = stoi(token);
        getline(ss, token, ','); m = stoi(token);
        getline(ss, token, ','); y = stoi(token);

        if (cid == id) {
            hrs -= decrease;
            if (hrs < 0) hrs = 0;
        }

        fout << cid << "," << name << "," << hrs << ","
             << d << "," << m << "," << y << endl;
    }

    fin.close();
    fout.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}


