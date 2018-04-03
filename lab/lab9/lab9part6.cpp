#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    friend ostream& operator<< (ostream& os, const PrintedMaterial material);
    PrintedMaterial () : numberOfPages(0) {}    
    PrintedMaterial(unsigned numberOfPages): numberOfPages(numberOfPages) {}
    void displayNumPages() const { cout << numberOfPages; }
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

ostream& operator<< (ostream& os, const PrintedMaterial material) {
    os << material.numberOfPages << endl;
}


// tester/modeler code
int main()
{
	TextBook t;
	Novel n;
	Magazine m;
    cout << m << n << t;
}