#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <vector>
#include <string>
// #include "Student.h"

namespace BrooklynPoly {
    class Student;
    class Course {
    public:
        Course(const std::string& name);
        void printReport() const;
        std::string getName() const;
        bool studentExists(const std::string& name);
        bool enrollStudentInCourse(Student* student);
        void cancelCourse();
    private:
        std::string name;
        std::vector<Student*> students;
    };
}
#endif