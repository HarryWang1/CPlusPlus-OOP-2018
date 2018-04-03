#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial () : numberOfPages(0) {}    
    //compiles since subclasses call printedMaterial with zero arguements
    PrintedMaterial(unsigned numberOfPages): numberOfPages(numberOfPages) {}
    //need the zero arguement in order to compile with tester code
protected:  
private:    
    unsigned numberOfPages;     
};

class Magazine : public PrintedMaterial {
public:
protected:
private:
};

class Book : public PrintedMaterial {
public:
protected:
private:
};

class TextBook : public Book {
public:
protected:
private:
};

class Novel : public Book {
public:
protected:
private:
};

// tester/modeler code
int main()
{
	TextBook t;
	Novel n;
	Magazine m;
}