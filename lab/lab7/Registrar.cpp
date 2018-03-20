#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Registrar.h"
#include "Student.h"
#include "Course.h"

namespace BrooklynPoly {
    Registrar::Registrar() {}
    void Registrar::printReport() const {
    cout << "-----\n\tUniversity Courses\n";
    for (const Course* course: courses) {
        course->printReport();
        cout << "\n";
    }
    cout << "-----\n";
    }
    bool Registrar::courseExists(const string& name) const {
        for (const Course* course: courses) {
            if (name == course->getName()) {
                return true;
            }
        }
        return false;
    }
    bool Registrar::addCourse(const string& name) {    //return true if success
        if (!courseExists(name)) {
        this->courses.push_back(new Course(name));
            return true;
        }
        return false;
    }
    bool Registrar::studentExists(const string& name) const {
        for (const Student* student: students) {
            if (name == student->getName()) {
                return true;
            }
        }
        return false;
    }
    bool Registrar::addStudent(const string& name) {   //return true if success
        if (!studentExists(name)) {
            this->students.push_back(new Student(name));
            return true;
        }
        return false;
    }
    Student* Registrar::findStudent(const string& name) {
        for (Student* student: students) {
            if (name == student->getName()) {
                return student;
            }
        }
    }
    Course* Registrar::findCourse(const string& name) {
        for (Course* course: courses) {
            if (name == course->getName()) {
                return course;
            }
        }
    }
    bool Registrar::enrollStudentInCourse(const string& student_name, const string& course_name) { //return true if success
        if (studentExists(student_name) && courseExists(course_name)) {
            Student* student = findStudent(student_name);   //find the student and course object
            Course* course = findCourse(course_name);
            return course->enrollStudentInCourse(student);   //returns true if success
        }
        return false;
    }
    bool Registrar::cancelCourse(const string& name) { //returns true if success
        if (courseExists(name)) {
            Course* course = findCourse(name);
            course->cancelCourse();     //delete course for each student
            for (size_t i = 0; i < courses.size(); ++i) {    //delete course from university registrar
                if (courses[i] == course) {
                    delete courses[i];
                    while (i+1 <= courses.size()) {
                        courses[i] = courses[i+1];
                        ++i;
                    }
                    courses.pop_back();
                }
            }
            return true;
        }
        return false;
    }
    void Registrar::purge() {       //delete all courses
        for (Course* course: courses) {
            course->cancelCourse();
        }
    }

    ostream& operator<<(ostream& os, const Registrar& registrar) {
        registrar.printReport();
        return os;
    }
}