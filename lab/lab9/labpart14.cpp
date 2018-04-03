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
    void displayNumPages() const {}
protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book( unsigned numPages ) : PrintedMaterial(numPages) {}
    void displayNumPages() const {}
protected:
private:
};

class TextBook : public Book {
public:
	TextBook(unsigned numPages, unsigned numIndxPgs) : Book(numPages), numOfIndexPages(numIndxPgs) {}
	void displayNumPages() const
	{
		cout << "index:" << numOfIndexPages << endl;
		cout << "pages: i need access to private member of printedmaterial";
        cout << "so define the method for printedmaterial outside of class. Trick!" << endl;
        PrintedMaterial::displayNumPages();
	}
protected:
private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel( unsigned numPages ) : Book(numPages) {}
    void displayNumPages() const {}
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

//YOU CAN DEFINE IT FOR THE ABSTRACT CLASS OUTSIDE OF THAT CLASS. USEFUL FOR TEXTBOOK PRINT. 
void PrintedMaterial::displayNumPages() const {
  cout << numOfPages << endl;
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


}