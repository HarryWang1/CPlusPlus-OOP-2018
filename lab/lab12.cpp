/*
Max Kim
Lab C
4/20/2018

*/

// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;

struct Node {
	Node* next;
    Node* prev;
    int data;

    Node(Node* next = nullptr, Node* prev = nullptr, int data = -1) {
        this->next = next;
        this->prev = prev;
        this->data = data;
    }

    void disconnect() {
        data = -1;
        next = nullptr;
        prev = nullptr;
    }
};


class List {
    friend ostream& operator<<(ostream& os, const List& list);
public:
    class iterator {
        friend class List;
    private:
        Node* p;
    public:
        iterator(Node* p) {
            this->p = p;
        }
        iterator& operator++() {
            this->p = this->p->next;
            return *this;
        }
        iterator& operator--() {
            this->p = this->p->prev;
            return *this;
        }
        bool operator==(const iterator& rhs) const {
            return this->p == rhs.p;
        }
        bool operator!=(const iterator& rhs) const {
            return !(this->operator==(rhs));
        }
        int operator*() {
            return p->data;
        }
    };

    List() {
	    header = new Node();
        trailer = new Node(nullptr, header, -1);
        header->next = trailer;
        this->theSize = 0;
    }

    int size() const {
        return this->theSize;
    }

    void push_back(int data) {
	    add_after(trailer->prev, data);
    }

    void add_after(Node* node, int data) {
        Node* new_node = new Node(node->next, node, data);
        node->next = new_node;
        new_node->next->prev = new_node;
        this->theSize += 1;
    }

    void pop_back() {
        if (this->theSize != 0) {
            del(this->trailer->prev);
        }
    }

    void del (Node* node) {
        Node* prev = node->prev;
        Node* succ = node->next;
        prev->next = succ;
        succ->prev = prev;
        this->theSize -= 1;
        delete node;
    }

    int front() const {
        if (this->theSize != 0) {
            return this->header->next->data;
        }
    }

    int back() const {
        if (this->theSize != 0) {
            return this->trailer->prev->data;
        }
    }

    void push_front(int data) {
        add_after(this->header, data);
    }

    void pop_front() {
        if (this->theSize != 0) {
            del(this->header->next);
        }
    }

    void clear() {
        while (this->theSize != 0) {
            pop_back();         //pop_back automatically connects nodes after deleting the last one
        }
    }

    int& operator[] (const int index) {
        if (index < this->theSize) {
            Node* curr = header->next;
            for (int i=0; i < index; ++i) {
                curr = curr->next;
            }
            return curr->data;
        }
    }
    const int operator[] (const int index) const {
        if (index < this->theSize) {
            Node* curr = header->next;
            for (int i=0; i < index; ++i) {
                curr = curr->next;
            }
            return curr->data;
        }
        return -1;
    }

    iterator begin() {
        return iterator(this->header->next);
    }
    iterator end() {
        return iterator(this->trailer);     //not the last element, but the one after the last element
    }

    const iterator begin() const {
        return iterator(this->header);
    }
    const iterator end() const {
        return iterator(this->trailer);
    }

    iterator insert(const iterator& i, int data) {
        add_after(i.p->prev, data);
        return iterator(i.p->next);
    }

    iterator erase(const iterator& i) {
        iterator after = iterator(i.p->next);   //save the node pointer that is after 
        del(i.p);       //how is it modifying if iterator is passed as const?
        return after;   
    }

    List(const List& rhs) {
        cout << "List(List)" << endl;
        //1. allocate new memory!!!
        header = new Node();
        trailer = new Node(nullptr, header, -1);
        header->next = trailer;
        this->theSize = 0;

        //2. copy over from the right side
        for (size_t i=0; i < rhs.size(); ++i) {
            this->push_back(rhs[i]);
        }
    }

    List& operator= (const List& rhs) {
        cout << "List::op=(List)" << endl;
        //1. check for yourself
        if (this != &rhs) {
            //2. delete old 
            this->clear();
            delete this->header;
            delete this->trailer;
            //3. allocate new memory
            header = new Node();
            trailer = new Node(nullptr, header, -1);
            header->next = trailer;
            this->theSize = 0;
            //4. copy over from the right side
            for (size_t i=0; i < rhs.size(); ++i) {
                this->push_back(rhs[i]);
            }
        }
        //5. return yourself
        return *this;
    }
    ~List() {
        cout << "~List()" << endl;
        this->clear();
        delete this->header;
        delete this->trailer;
    }

private:
    Node* header;
    Node* trailer;
    int theSize;
};

ostream& operator<<(ostream& os, const List& list) {
	Node* curr = list.header->next;
	while (curr != list.trailer) {
		os << curr->data << ' ';
        curr = curr->next;
    }
    return os;
}

void printListInfo(List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}    

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";

    // Task3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
    
}
