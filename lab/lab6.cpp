/*
Max Kim
Lab C
March 2 2018

A program that simulates the grading system of a lab. Practice for Copy control and dynamic arrays
*/

#include <string>
#include <iostream>
using namespace std;

class Position {
public:
    Position(const string& aTitle, double aSalary) : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
    void display(ostream& os = cout) const {
        os << '[' << title << ',' << salary << ']';
    }
private:
    string title;
    double salary;
}; // class Position

class Entry {
public:
    Entry(const string& aName, unsigned aRoom, unsigned aPhone, Position& aPosition) 
	: name(aName), room(aRoom), phone(aPhone), pos(&aPosition) {
    }
    void display(ostream& os = cout) const {
        os << name << ' ' << room << ' ' << phone << ", ";
        pos->display(os);
    }
    const string& getName() const { return name; }
    const unsigned& getPhone() const { return phone; }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;      //pointer to position object
}; // class Entry

class Directory {
public:
    ~Directory() {
        cout << "Entered the destructor of Directory\n";
        for (size_t i=0; i < this->size; ++i) {     //calls destructor of each pointer within array
            delete entries[i];
        }
        delete[] entries;   //delete the outer array
    }
    Directory() {
        cout << "Entered the zero arguement constructor of directory\n";
		entries = new Entry*[1];                    //make initialize size of array as 1 size
    }
    Directory(const Directory& rhs) {
        cout << "Entered the copy constructor of Directory\n";
        this->size = rhs.size;                      //set left hand side
        this->capacity = rhs.capacity;              
        this->entries = new Entry*[capacity];       //deep copy right side. MAKE SURE to use RIGHT HAND SIDE SIZE AND CAPACITY either by saying rhs.size or set lhs's size as rhs.size beforehand
        for (size_t i = 0; i < size; ++i) {
			entries[i] = new Entry(*(rhs.entries)[i]);		//call default copy constructor of entry, make sure its on heap
        }
    }
    Directory& operator=(const Directory& rhs) {
        cout << "Entered the assignment operator of Directory\n";
        if (this == &rhs) {     //check that you are not yourself
            return *this;
        }
        for (size_t i=0; i < this->size; ++i) {     //calls destructor of each pointer within array
            delete this->entries[i];
        }
        delete[] this->entries;                     //delete left hand side
        Entry** new_entries = new Entry*[rhs.capacity];     //deep copy right side
        for (size_t i = 0; i < rhs.size; ++i) {
			new_entries[i] = new Entry(*(rhs.entries)[i]);		//call default copy constructor of entry, make sure its on heap
        }
		this->entries = new_entries;                 //set left hand
        this->size = rhs.size;                     
        this->capacity = rhs.capacity;
        return *this;
    }
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
		cout << "Entered the add fuction of directory\n";
		if (size == capacity)	{	                        //expand the array 
			capacity *= 2;
			Entry** new_entries = new Entry*[capacity];     //make new entries
			for (size_t i = 0; i < this->size; ++i) {       //shallow copy over. Meaning new array but the pointers within the array are NOT copied. 
				new_entries[i] = entries[i];
			}
            delete[] entries;                               //delete ONLY old entry, not the pointers within
			entries = new_entries;                          //make entries point to new one
		}
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add
    unsigned operator[](const string& name) const {       //overload [] operator to return phone # from name
        for (size_t i = 0; i < size; ++i) {
            if (entries[i]->getName() == name) {
                return entries[i]->getPhone();
            }
        }
    }
    void display(ostream& os = cout) const {
        for (size_t i = 0; i < size; ++i) {
            entries[i]->display(os);
            os << endl;
        }
    }

private:	
    Entry** entries = nullptr;  //point to an array of pointers to entries
    size_t size = 0;
    size_t capacity = 1;
}; // class Directory

void doNothing(Directory dir) { dir.display(); }

ostream& operator<< (ostream& os, const Directory& item) {
    item.display(os);
	return os;
}

int main() {
	
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
	
    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    d.display();

    Directory d2 = d;	// calls the copy constructor, not the assignment operator
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    d2.display();

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;

    // Should display 1592
    cout << d2["Carmack"] << endl;
	
} // main
