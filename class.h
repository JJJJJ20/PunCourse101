#include <string>

struct expiration_date{
    int d, m, y;
};
typedef struct expiration_date EXP;


class Course{
private:
    int course_id;
    string name;
    float hours;
    EXP exp;
    //Course *next;
public:
    Course(int id, string n, float hrs, EXP ex);
    ~Course();
    void print_course();
    void input_course();
};
typedef Course* CoursePtr;



//cop jak chatGPT
class Progress {
    public:
        Course* course;
        int completed_hours;
        float score;
    
        Progress(Course* c, int hours, float s) {
            course = c;
            completed_hours = hours;
            score = s;
        }
    };