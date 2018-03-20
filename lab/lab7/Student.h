#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>
// #include "Course.h"

namespace BrooklynPoly {
    class Course;
    class Student {
    public:
        Student(const std::string& name);
        void printReport() const;
        std::string getName() const;
        void cancelCourse(Course* course);
    private:
        std::string name;
        std::vector<Course*> courses;
    };
}
#endif