#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
	PrintedMaterial( unsigned numPages ) : numOfPages(numPages) {}
	virtual void displayNumPages() const = 0;
protected:
private:
	unsigned numOfPages;
};

//YOU CAN DEFINE IT FOR THE ABSTRACT CLASS OUTSIDE OF THAT CLASS. USEFUL FOR TEXTBOOK PRINT. 
void PrintedMaterial::displayNumPages() const {
  cout << numOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
	Magazine( unsigned numPages ) : PrintedMaterial(numPages) {}
    void displayNumPages() const {      
    //don't have to say this method is virtual again. Already said in base
        cout << "pages: ";
        PrintedMaterial::displayNumPages();
    }
protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book( unsigned numPages ) : PrintedMaterial(numPages) {}
    void displayNumPages() const {
        cout << "pages: ";
        PrintedMaterial::displayNumPages();
    }
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
        cout << "so define the method for printedmaterial outside of class. Trick! pages:" << endl;
        PrintedMaterial::displayNumPages();
	}
protected:
private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel( unsigned numPages ) : Book(numPages) {}
    void displayNumPages() const {
        cout << "pages: ";
        PrintedMaterial::displayNumPages();
    }
protected:
private:
};

// tester/modeler code
int main()
{
    vector<PrintedMaterial*> list;
	TextBook t(5430, 234);
	Novel n(213);
	Magazine m(6);
    list.push_back(&t);
    list.push_back(&n);
    list.push_back(&m);
  
    for (PrintedMaterial* anypm: list) {
        anypm->displayNumPages();
    }

}