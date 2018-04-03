#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    //PrintedMaterial () : numberOfPages(0) {}    
    PrintedMaterial(unsigned numberOfPages): numberOfPages(numberOfPages) {}
protected:  
private:    
    unsigned numberOfPages;     
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numberOfPages): PrintedMaterial(numberOfPages) {}
protected:
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numberOfPages): PrintedMaterial(numberOfPages) {}
protected:
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numberOfPages): Book(numberOfPages) {}
protected:
private:
};

class Novel : public Book {
public:
    Novel(unsigned numberOfPages): Book(numberOfPages) {}
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