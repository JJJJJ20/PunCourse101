#include "progress.h"
#include "login.h"
#include <algorithm>
#include <fstream>
#include <sstream>
LoginSystem sys;

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
                cout << "You cannot complete more than remaining hours. Adjusted to maximum."<<endl;
                sys.waitForEnter();
                done = remaining;
                remaining -= done;
            } else{
                remaining -= done;
                  cout << "Updated: " << name << " -> Completed: " << total - remaining
                   << "/" << total << " (" << remaining << " hours left)\n";
                 sys.waitForEnter();
            }
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
        sys.waitForEnter();
    }
}





