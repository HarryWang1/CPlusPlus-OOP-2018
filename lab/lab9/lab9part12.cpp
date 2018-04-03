#include <iostream>
using namespace std;

class PrintedMaterial {
public:
	PrintedMaterial( unsigned numPages ) : numOfPages(numPages) {}
	virtual void displayNumPages() const { cout << numOfPages << endl; }
protected:
private:
	unsigned numOfPages;
};

class Magazine : public PrintedMaterial {
public:
	Magazine( unsigned numPages ) : PrintedMaterial(numPages) {}
protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book( unsigned numPages ) : PrintedMaterial(numPages) {}
protected:
private:
};

class TextBook : public Book {
public:
	TextBook(unsigned numPages, unsigned numIndxPgs) : Book(numPages), numOfIndexPages(numIndxPgs) {}
	void displayNumPages() const
	{
		cout << "index:" << numOfIndexPages << endl;
		cout << "pages:";
        PrintedMaterial::displayNumPages();
	}
protected:
private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel( unsigned numPages ) : Book(numPages) {}
protected:
private:
};

// tester/modeler code
int main()
{
	TextBook t(5430, 234);
	Novel n(213);
	Magazine m(6);

	t.displayNumPages();
	n.displayNumPages();
	m.displayNumPages();

    PrintedMaterial* pmPtr;
    pmPtr = &t;             
    //pointer stores address to textbook object. So it should call textbook's method.
    pmPtr->displayNumPages();
//it does not. Calls printedmaterial's method because you only get the base class when you dereferenced
//the base call pointer.
//how to fix it? use virtual. When you dereference a pointer to an base class which has a virtual 
//you get the DERIVED class.

}