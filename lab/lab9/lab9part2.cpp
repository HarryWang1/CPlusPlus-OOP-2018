#include <iostream>
using namespace std;

class PrintedMaterial {
public:
protected:
private:
    unsigned numberOfPages;         //private members are not inherited
};

class Magazine : public PrintedMaterial {
public:
protected:
private:
    unsigned numberOfPages;
};

class Book : public PrintedMaterial {
public:
protected:
private:
    unsigned numberOfPages;
};

class TextBook : public Book {
public:
protected:
private:
    unsigned numberOfPages;
};

class Novel : public Book {
public:
protected:
private:
    unsigned numberOfPages;
};

// tester/modeler code
int main()
{
	TextBook t;
	Novel n;
	Magazine m;
}