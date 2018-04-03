#include <iostream>
using namespace std;

class PrintedMaterial {
public:
	PrintedMaterial( unsigned numPages ) : numOfPages(numPages) {}
	virtual void displayNumPages() const = 0;
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

// note that reference to PrintedMaterial is the parameter type
// so now we can use the dot member operator (the .)
// if use the -> operator, that's not going to work
void displayNumberOfPages(const PrintedMaterial& pm) {
    pm.displayNumPages();
}
void displayNumberOfPagesPOINTER( const PrintedMaterial* anyPM )
{
	anyPM->displayNumPages();
}

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
    displayNumberOfPages(*pmPtr);
    displayNumberOfPagesPOINTER(pmPtr);

}