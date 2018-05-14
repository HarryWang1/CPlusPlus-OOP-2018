/*
MAX KIM
A program to test out linked lists and create some functions to modify and use them
April 13 2018

*/


#include <cstdlib> // To allow NULL if no other includes
#include <iostream>
#include <vector>
using namespace std;
#include <unordered_set>

struct Node {
	Node(int data = 0, Node* next = NULL) : data(data), next(next) {}
	int data;
	Node* next;
};

void listInsertHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

// Should free up your nodes, of course...
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;         //save what comes after
        delete headPtr;                     //delete
        headPtr = next;                     //point to next
    }
}

// This might be useful for setting up test cases. Feel free to use it
// or not as you like. Example of using would be:
// Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    //go backwards to account for inserting at head
    for (size_t index = vals.size(); index > 0; --index) { 
        listInsertHead(result, vals[index-1]);
    }
    return result;
}

void insertAfter(Node* nodeToAddAfter, Node* headPtrOfOtherNode) {
    //1. save the node after the nodeToAddAfter
    Node* nextNode = nodeToAddAfter->next;
    //2. set the next as the head of the other node
    nodeToAddAfter->next = headPtrOfOtherNode;
    //3. set the very last node of other node's next as the saved node
    Node* lastNode = headPtrOfOtherNode;
    while (lastNode->next != nullptr) {
        lastNode = lastNode->next;
    }
    lastNode->next = nextNode;
    //step 3 is needed because we don't know how long the node that we insert is. 
}

void printList(Node* headPtr) {
    while (headPtr != nullptr) {
        cout << headPtr->data << ' ';
        headPtr = headPtr->next;
    }
    cout << endl;
}

Node* isSublist(Node* headPtrList, Node* headPtrSublist) {
    //check for nullptr first
    if (!headPtrSublist) {
        return nullptr;
    }
    //1. travel through List and try to find starting point where data are same
    while (headPtrList != nullptr) {
        if (headPtrList->data == headPtrSublist->data) {
            //2. If a match is found, Keep going through both lists and repeat test
            //make copies of sublist and save the starting point
            Node* copySublist = headPtrSublist; 
            Node* possibleAnswer = headPtrList;     
            while (headPtrList != nullptr && copySublist != nullptr) {
                //3. if test fails, continue on from headPtrList's place.
                if (headPtrList->data != copySublist->data) {
                    break;
                }
                copySublist = copySublist->next;
                headPtrList = headPtrList->next;
                //continue if match
            }
            //4. test was successful since the sublist has reached its end. Return starting node.
            if (copySublist == nullptr) {   
                cout << "Found an answer! Will print out the node." << endl;  
                return possibleAnswer;
            }
        }
        //additional test needed for when headPtrList runs out in above while loop
        if (headPtrList != nullptr) {       
            headPtrList = headPtrList->next;
        }
    }
    //5. no match was found.
    return nullptr; 
}

Node* isSublistTwo(Node* headPtrL1, Node* headPtrL2) {
    //1. create a set of L1. Convert from linked list to an unordered set.
    unordered_set<Node*> L1;
    while (headPtrL1 != nullptr) {
        L1.insert(headPtrL1);
        headPtrL1 = headPtrL1->next;
    }
    //2. call find() on each Node in L1 from L2. 3. check if found and return answer
    if (L1.end() == L1.find(headPtrL2)) {
        return nullptr;
    } else {
        cout << "Found answer!";
        return headPtrL2;
    }

}

int main() {
    //part 1
    Node* list1 = listBuild({1, 4, 9, 16});
    Node* list2 = listBuild({5, 5, 5, 5});
    printList(list1);
    insertAfter(list1, list2);
    printList(list1);
    printList(list2);

    cout << endl << "################# Part 2 ##############" << endl;
    //part 2
    cout << endl;
    Node* mainList = listBuild({5, 7, 6, 3, 2, 9, 1});
    Node* list3 = listBuild({6, 3, 2, 9});
    printList(mainList);
    printList(list3);
    printList(isSublist(mainList, list3));      //print out the node pointer that is returned
    cout << endl;
    Node* list4 = listBuild({6, 2, 3});
    printList(mainList);
    printList(list4);
    printList(isSublist(mainList, list4));
    cout << endl;
    Node* list5 = listBuild({2, 9, 1, 4});
    printList(mainList);
    printList(list5);
    printList(isSublist(mainList, list5));
    cout << endl;
    Node* test = listBuild({5, 1, 4});
    Node* test1 = listBuild({2, 9, 10, 11});
    printList(test);
    printList(test1);
    printList(isSublist(test, test1));
    cout << endl;
    Node* test2 = listBuild({5, 7, 6, 3, 2, 9, 1});
    printList(mainList);
    printList(test2);
    printList(isSublist(mainList, test2));
    cout << endl;

    cout << "################## Part 3 ####################" << endl;
    //part 3
    Node* test3 = listBuild({1, 2, 3, 4, 5});
    Node* test4 = listBuild({5, 5});
    printList(test3);
    printList(test4);
    insertAfter(test3, test4);
    printList(test3);
    printList(test4);
    printList(isSublistTwo(test3, test4));

    //Cleanup!
    //listClear(list2);
    //listClear(test4);

    listClear(test3);
    listClear(list1);
    listClear(test2);
    listClear(test1);
    listClear(test);
    listClear(list5);
    listClear(list4);
    listClear(list3);
    listClear(mainList);
}
