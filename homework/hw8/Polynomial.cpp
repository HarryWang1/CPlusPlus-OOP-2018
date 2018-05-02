#include "Polynomial.h"
#include <iostream>
#include <vector>
#include <cmath>    //used for exponential function ^
#include <string>   
#include <algorithm>
using namespace std;

/*
Max Kim
Section A
May 2 2018
Implement a class Polynomial for storing and manipulating polynomial expressions
Store each polynomial as a degree and a singly linked list of its coefficients, but in backwards order
The list for a non-zero polynomial does not end with a zero coefficient. 
The value of the degree member variable is one less than the length of the list.
*/

Node::Node(double data, Node* next):data(data), next(next) {}

void listAddHead(Node*& headPtr, double data) {
    headPtr = new Node(data, headPtr);
}
void listAddTail(Node*& headPtr, int data) {    
    if (headPtr == nullptr) {
        headPtr = new Node(data);   
    } else {
        Node* last = headPtr;
        while (last->next != nullptr) {     
            last = last->next;
        }
        last->next = new Node(data);
    }
}
int listLength(Node* headPtr) {
    Node* p = headPtr;
    int counter = 0;
    while (p != nullptr) {
        ++counter;
        p = p->next;
    }
    return counter;
}
Node* listDuplicate(Node* headPtr) {
    if (headPtr == nullptr) {
        return nullptr;
    }
    Node* result = new Node(headPtr->data);
    Node* last = result;
    Node* curr = headPtr->next;
    while (curr != nullptr) {  
        last->next = new Node(curr->data);
        curr = curr->next;
        last = last->next;
    }
    return result;
}
bool listRemoveHead(Node*& headPtr) {
    if (headPtr != nullptr) {
        Node* second = headPtr->next;
        delete headPtr;         
        headPtr = second;
        return true;
    }
    return false;
}
void listClear(Node*& headPtr) {
    while (headPtr != nullptr) {
        listRemoveHead(headPtr);
    }
}

//constructor that takes a vector of its coefficients in order from highest degree term to lowest
Polynomial::Polynomial() {
    this->headPointer = nullptr;
    this->degree = 0;
}
Polynomial::Polynomial(const vector<double>& coefficients) : headPointer() {
    for (double number: coefficients) {
        listAddHead(headPointer, number);
    }
    this->degree = coefficients.size()-1;
}
Polynomial::Polynomial(const Polynomial& rhs) : headPointer() {
    this->headPointer = listDuplicate(rhs.headPointer);
    this->degree = rhs.degree;
}
Polynomial& Polynomial::operator=(const Polynomial& rhs) {
    if (this != &rhs) {
        //1. free up resources
        listClear(this->headPointer);
        //2. allocate new resources
        //3. copy over
        this->headPointer = listDuplicate(rhs.headPointer);
        this->degree = rhs.degree;
    }
    return *this;
}
Polynomial::~Polynomial() {
    listClear(this->headPointer);
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    Node* lhs_curr = this->headPointer;
    Node* rhs_curr = rhs.headPointer;
    //iterate through lhs and add rhs's corresponding data.
    if (this->degree >= rhs.degree) {
        while (rhs_curr != nullptr) {
            lhs_curr->data += rhs_curr->data;
            lhs_curr = lhs_curr->next;
            rhs_curr = rhs_curr->next;
        }
    //rhs has more digits than lhs. Need to add extra digits.
    } else {
        //copy over until you reach end of lhs, which is smaller
        while (lhs_curr != nullptr) {
            lhs_curr->data += rhs_curr->data;
            lhs_curr = lhs_curr->next;
            rhs_curr = rhs_curr->next;
        }
        //then add on rhs's stuff to the tail of lhs
        while (rhs_curr != nullptr) {
            listAddTail(headPointer, rhs_curr->data);
            rhs_curr = rhs_curr->next;
        }
        //change the degree 
        this->degree = listLength(this->headPointer);
    }
    return *this;
}
bool Polynomial::operator== (const Polynomial& rhs) {
    //1. check that degrees are the same
    if (this->degree == rhs.degree) {
        Node* lhs_curr = this->headPointer;
        Node* rhs_curr = rhs.headPointer;
        //run through both and return false if a digit is not the same
        while (lhs_curr != nullptr) {
            if (lhs_curr->data != rhs_curr->data) {
                return false;
            }
            lhs_curr = lhs_curr->next;
            rhs_curr = rhs_curr->next;
        }
        return true;
    }
    return false;
}
bool Polynomial::operator!= (const Polynomial& rhs) {
    return !(operator==(rhs));
}

//evaluates the polynomial by plugging in the value of x for X
double Polynomial::evaluate(int x) const {
    double answer = 0;
    Node* curr = this->headPointer;
    int counter = 0;
    while (curr != nullptr) {
        answer += (curr->data * (pow(x, counter)));
        ++counter;
        curr = curr->next;
    }
    return answer;
}


Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial result(lhs);     //utilize copy constructor
    result += rhs;              //utilize the += operator 
    return result;              //return a brand new Polynomial with lhs and rhs added
}

ostream& operator<<(ostream& os, const Polynomial& item) {
    string answer = "";
    Node* curr = item.headPointer;
    int counter = 0;
    //special case when empty, just print out 0
    if (curr == nullptr) {
        cout << "0" << endl;
    }
    //have a string called answer and insert at the beginning. Since you need to print 1 + x, not x + 1
    //which is backwards of how it is stored
    while (curr != nullptr) {
        if (curr->data ==0) {
            //skip if 0 
        } else if (counter==0) {
            answer.insert(0, to_string(int(curr->data))+" + ");
        } else if (counter==1){
            answer.insert(0, to_string(int(curr->data))+"x + ");
        } else {
            answer.insert(0, to_string(int(curr->data))+"x^"+to_string(counter)+" + ");
        }
        ++counter;
        curr = curr->next;
    }
    //remove the last + sign
    cout << answer.substr(0, answer.size()-3) << endl;
    return os;
}


void doNothing(Polynomial temp) {}

int main() {
	
    //test constructor
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -1x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7
	
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;
    cout << "has_a_zero: " << has_a_zero << endl;
    cout << "p2 + p3: " << (p2+p3) << endl; 
    cout << "p2 + p4: " << (p2+p4) << endl; 
    cout << "p4 + p2: " << (p4+p2) << endl;


    //test copy constructor - the statement below uses the copy constructor
    //to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;  
    cout << "p5: " << p5 << endl;  

    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator
    Polynomial p6;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    p6 = p4;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;

    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
	
    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;
}

