/*
Max Kim
Lab C
May 4 2018
Recursion
*/
#include <iostream>
#include <exception>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////
struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr) : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};
struct Node {
    Node(int data =0, Node* next = nullptr): data(data), next(next) {}
    int data;
    Node* next;
};


//Write a recursive function to determine if a non-negative integer has an even number of ones in its binary 
//representation. Return true if it does and false otherwise.
//return true if number is 1, and return false if number is 0. Compare this one and the next one to determine
//evenOnes says if the rest of numbers have even number of ones. So if you also have another one, then you
//become odd. If you dont have a one, then you stay even. 

bool evenOnes(int n) {
    if (n == 0) {
        return true;
    }
    if (n == 1) {
        return false;
    }
    if (n%2==0) {
        return evenOnes(n/2);
    //all functions below: n%2==1. 
    } else if (evenOnes(n/2)) {
        return false;
    } else if (evenOnes(n/2) == false) {
        return true;
    } 
}

//Write a recursive function to create and return a new list that is the sum of the values in the the two lists 
//passed in. Do not assume that the two lists are the same length.

//get sum of the first and second's data. Then pass in recursively with first and second's next pointer. But 
//check if first and second are nullptr before and change accordingly. Create new nodes with sum.

Node* sumOfTwoLists(Node* first, Node* second) {
    if (first == nullptr && second == nullptr) {
        return new Node(0);
    } else if (first == nullptr) {
        return new Node(second->data + sumOfTwoLists(first, second->next)->data);
    } else if (second == nullptr) {
        return new Node(first->data + sumOfTwoLists(first->next, second)->data);
    }
    Node* otherSums = sumOfTwoLists(first->next, second->next);
    return new Node(first->data + second->data + otherSums->data);
}

//Write a recursive function to return the maximum value in a binary tree.
//compare the value in the node that you are looking at with the left and right's value. Return the max of those 3
//save initial sum of left and right as zero and update after checking if not nullptr.
int maxOfBinaryTree(TNode* root) {
    if (root == nullptr) {
        throw invalid_argument("Tree is empty");
    }
    int mid = root->data;
    int left = 0;                       //save values to default to zero beforehand
    int right = 0;
    if (root->left != nullptr) {        //check if not nullptr beforehand so no error 
        left = maxOfBinaryTree(root->left);
    }
    if (root->right != nullptr) {
        right = maxOfBinaryTree(root->right);
    }
    return max(mid, max(left, right));  //return the greatest of those 3
} 

//Write a recursive function called palindrome that determines if a char array is a palindrome.
//check if the first and last are same and also check the second and penultimate are also same. 
bool palindrome(char s[], int size) {
    if (size < 2) {         //only one or zero letters. 
        return true;
    }
    //dereference the address, but the [] operator doesnt need a dereference. Decrease size as you go and 
    //increase the address to point to the next address or item
    return *s == s[size-1] && palindrome(s+1, size-2);
}

//write a recursive function that returns the number of moves needed to complete towers of hanoi.
int towers(int n, char start, char target, char spare) {
    if (n==0) return 0;
    return 1 + towers(n-1, start, spare, target) + towers(n-1, spare, target, start);
}

//find out what the function returns for values 0 to 10
void mystery(int n) { 
   if (n > 1) { 
      cout << 'a'; 
      mystery(n/2); 
      cout << 'b'; 
      mystery(n/2); 
   } 
   cout << 'c'; 
}



int main() {
    //task 1

    cout << "13 " << boolalpha<< evenOnes(13) << endl;
    cout << "5 " << boolalpha << evenOnes(5) << endl;
    cout << "3 " << boolalpha << evenOnes(3) << endl;
    cout << "2 " << boolalpha << evenOnes(2) << endl;
    cout << "8 " << boolalpha << evenOnes(8) << endl;
    //task 2

    //task 3
    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
    cout << maxOfBinaryTree(&f) << endl;
    //cout << maxOfBinaryTree(nullptr) << endl;     //test for nullptr empty tree
    //task 4
    char s[] = "racecar";
    if (palindrome(s, 7)) { cout << "Yes!\n"; }
    //task 5
    cout << "1 " << towers(1, 'a', 'b', 'c') << endl;
    cout << "3 " << towers(2, 'a', 'b', 'c') << endl;
    cout << "7 " << towers(3, 'a', 'b', 'c') << endl;
    cout << "15 " << towers(4, 'a', 'b', 'c') << endl;
    cout << "31 " << towers(5, 'a', 'b', 'c') << endl;
    cout << "63 " << towers(6, 'a', 'b', 'c') << endl;
    //task 6
    //before running the function, I predict these values
    //0     'c'
    //1     'c'
    //2     'a' 'c' 'b' 'c'
    //3     'a' 'c' 'b' 'c'
    //4     'a' 'a' 'c' 'b' 'c' 'b' 'a' 'c' 'b' 'c'
    //5     'a' 'a' 'c' 'b' 'c' 'b' 'a' 'c' 'b' 'c'
    //6     'a' 'a' 'c' 'b' 'c' 'b' 'a' 'c' 'b' 'c'
    //7     'a' 'a' 'c' 'b' 'c' 'b' 'a' 'c' 'b' 'c'
    //8     'a' 'a' 'a' 'c' 'b' 'c' 'b' 'a' 'c' 'b' 'c' 'b' 'a' 'a' 'c' 'b' 'c' 'b' 'a' 'c' 'b' 'c'
    //9     'a' 'a' 'a' 'c' 'b' 'c' 'b' 'a' 'c' 'b' 'c' 'b' 'a' 'a' 'c' 'b' 'c' 'b' 'a' 'c' 'b' 'c'
    //10    'a' 'a' 'a' 'c' 'b' 'c' 'b' 'a' 'c' 'b' 'c' 'b' 'a' 'a' 'c' 'b' 'c' 'b' 'a' 'c' 'b' 'c'
}