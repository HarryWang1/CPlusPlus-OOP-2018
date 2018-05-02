/*
Max Kim
Section A
May 2 2018
Implement a class Polynomial for storing and manipulating polynomial expressions
Store each polynomial as a degree and a singly linked list of its coefficients, but in backwards order
The list for a non-zero polynomial does not end with a zero coefficient. 
The value of the degree member variable is one less than the length of the list.
*/

#ifndef POLYNOMIAL_H 
#define POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <cmath>    //used for exponential function ^
#include <string>   
#include <algorithm>


struct Node {
    Node(double data=0, Node* next=nullptr);
    double data;
    Node* next;
};

void listAddHead(Node*& headPtr, double data);
void listAddTail(Node*& headPtr, int data);
int listLength(Node* headPtr);
Node* listDuplicate(Node* headPtr);
bool listRemoveHead(Node*& headPtr);
void listClear(Node*& headPtr);

class Polynomial {
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& item);
public:
    Polynomial();
    Polynomial(const std::vector<double>& coefficients);
    Polynomial(const Polynomial& rhs);
    Polynomial& operator=(const Polynomial& rhs);
    ~Polynomial();

    Polynomial& operator+=(const Polynomial& rhs);
    bool operator== (const Polynomial& rhs);
    bool operator!= (const Polynomial& rhs);

    double evaluate(int x) const;
private:
    Node* headPointer;
    int degree;
};

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
std::ostream& operator<<(std::ostream& os, const Polynomial& item);

#endif