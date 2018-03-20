#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
    Student::Student(const string& name): name(name) {}
    void Student::printReport() const {
        cout << this->name << "\n";
    }
    string Student::getName() const {
        return this->name;
    }
    void Student::cancelCourse(Course* course) {     //find and take out without any special functions
        for (size_t i = 0; i < courses.size(); ++i) {
            if (courses[i] == course) {
                while (i+1 <= courses.size()) {
                    courses[i] = courses[i+1];
                    ++i;
                }
                courses.pop_back();     
            }
        }
    }
}