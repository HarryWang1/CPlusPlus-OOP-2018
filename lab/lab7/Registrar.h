#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <iostream>
#include <string>
#include <vector>
// #include "Student.h"
// #include "Course.h"

namespace BrooklynPoly {
    class Course;
    class Student;

    class Registrar {
    public:
        friend std::ostream& operator<<(std::ostream& os, const Registrar& registrar);
        Registrar();
        void printReport() const;
        bool courseExists(const std::string& name) const;
        bool addCourse(const std::string& name);
        bool studentExists(const std::string& name) const;
        bool addStudent(const std::string& name);
        Student* findStudent(const std::string& name);
        Course* findCourse(const std::string& name);
        bool enrollStudentInCourse(const std::string& student_name, const std::string& course_name);
        bool cancelCourse(const std::string& name);
        void purge();
    private:
        std::vector<Course*> courses;
        std::vector<Student*> students;
    };
}
#endif