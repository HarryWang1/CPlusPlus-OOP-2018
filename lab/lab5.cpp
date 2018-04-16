/*
MAX KIM
Lab C
February 23 2018
This program models the grading process of a typical class with a lab section. There are lab sections,
lab instructors, and lab students.

OVERVIEW
class instructor
  name of instructor
  section pointer
  display()	← overload cout
	 display the grades for their section

class section
	vector of student pointers;
  time_slot
	display()	← overload cout
    section name, the day and hour, the lab worker's name, all the students. Time should be should in AM or PM
	reset()
		clears out the data for the student records

  class time_slot
		day of week (string)
		hour that lab starts (int)

	class student (students should be on heap)
		name of student
    vector weekly grades;	← absence is -1, everyone absent b4 first grade
		copy constructor
		destructor
		assignment operator
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class LabWorker;

class Section {
  friend class LabWorker;
  public:
    //constructor
    Section(const string& name, const string& day, int hour) : name(name), time(day, hour) {}
    //copy constructor
    Section(const Section& section) : name(section.name), time(section.time.day, section.time.hour) {
    	for (Student* student: section.students) {
    		Student* new_student = new Student(*student);	//call the student's default constructor
    		this->students.push_back(new_student);
    	}
    }
    //destructor
    ~Section() {
    	cout << "Section " << this->name << " is being deleted\n";
    	for (Student* student: this->students) {
    		cout << "Deleting " << student->name <<"\n";
    		delete student;
    		student = nullptr;
    	}
    }

    //section name, the day and hour, all the students.
    void display(ostream& os) const {
  		os << "Section: " << this->name << ", Time slot: " << this->time.getTime() << ", Students: ";
  		if (this->students.size() == 0) {
    		os << "None";
  		} else {
    		for (Student* student: this->students) {
      		os << "\n Name: " << student->name << ", Grades: ";
      		for (int grade: student->grades) {
        		os << grade << " ";
      		}
    		}
  		}
  		os << "\n";
		}

    //clears out the data for the student records ... manually call deconstructor from here?
    void reset() {

    }
    void addStudent(const string& student_name) {
    	Student* pointer = new Student(student_name);
    	this->students.push_back(pointer);
    }
    //chain down the adding of student grade to the student class
    void callStudentAddGrade(const string& student_name, int grade, int week_number) {
    	for (Student* student : students) {
    		if (student_name == student->name) {
    			student->addGrade(grade, week_number);
    			break;
    		}
    	}
    }
  private:
    class Student {
      friend class Section;
      public:
        //constructor
        Student(const string& name) : name(name), grades(14, -1){}//{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1} {}
        void addGrade(int grade, int week_number) {
        	grades[week_number-1] = grade;
        }
      private:
        string name;
        vector<int> grades;
    };
    class Time_slot {
      friend class Section;
      public:
        //constructor
        Time_slot(const string& day, int hour) : day(day), hour(hour) {}
        //return time in AM or PM and day in format
        string getTime() const {
          if (this->hour > 12) {
            return "[Day: " + day + ", Start time: " + to_string((hour-12)) + "pm]";
          } else {
            return "[Day: " + day + ", Start time: " + to_string(hour) + "am]";
          }
        }
      private:
        string day;
        int hour;
    };
    string name;
    vector<Student*> students;
    Time_slot time;
};

class LabWorker {
  public:
    //constructor
    LabWorker(const string& name) : name(name), section(nullptr) {}
    //display the grades for their section
    void display(ostream& os) const {
    	if (this->section == nullptr) {
    		os << this->name << " does not have a section\n";
    	} else {
    		os << this->name << " has ";
    		section->display(os);
    	}
    }
    // add a section to labworker
    void addSection(Section& section) {
      this->section = &section;
    }
    // add a grade for a student
    void addGrade(const string& student_name, int grade, int week_number) {
      this->section->callStudentAddGrade(student_name, grade, week_number);
    }
  private:
    string name;
    Section* section;
};


//display the grades for their section
ostream& operator<< (ostream& os, const LabWorker& TA) {
	TA.display(os);
	return os;
}
//section name, the day and hour, all the students.
ostream& operator<< (ostream&os, const Section& section) {
	section.display(os);
	return os;
}


// Test code
void doNothing(Section sec) { cout << sec; }

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
   	secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
   	secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, then make sure the following call works\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main
