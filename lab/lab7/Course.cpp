#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
    Course::Course(const string& name): name(name){}

    void Course::printReport() const {
        cout << "Course: " << this->name << "\nStudents: ";
        for (const Student* student: students) {
            cout << "\t";
            student->printReport();
        }
    }

    string Course::getName() const {
        return this->name;
    }

    bool Course::studentExists(const string& name) {
        for (const Student* student: students) {
            if (name == student->getName()) {
                return true;
            }
        }
        return false;
    }

    bool Course::enrollStudentInCourse(Student* student) {  //returns true if success
        if (!studentExists(student->getName())) {
            students.push_back(student);
            return true;
        }
        return false;
    }

    void Course::cancelCourse() {       //delete the course from each student
        for (Student* student: students) {  
            student->cancelCourse(this);
        }
    }
    
}