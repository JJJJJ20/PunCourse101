#include<iostream>
using namespace std;

#include "course.h"


int main(int argc, char *argv[]){
    //Course A; //ประกาศงี้ไม่ได้ ต้องกำหนดค่า or set default values
    EXP a;
    a.d = 10;
    a.m = 10;
    a.y = 2005;
    //A = new Course(123, "MathTCAS", 234.5 , a); //อันนี้ใช้ได้แค่กับ pointer
    Course A(123, "MathTCAS", 234.5, a);
    A.input_course();
    A.print_course();
    
}