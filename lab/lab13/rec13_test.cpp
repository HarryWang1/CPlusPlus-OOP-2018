/* rec13_test.cpp
Max Kim
Lab C
April 27 2018
*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <set>         // task 20
#include <map>         // task 22
using namespace std;

//task 9 functions
/*
void nonConstIteratorPrint(const list<int>& items) {
    list<int>::iterator ptr1;
    for (ptr1 = items.begin(); ptr1 != items.end(); ++ptr1) { 
        cout << *ptr1 << ' ';
    }
}
*/
void constIteratorPrint(const list<int>& items) {
    list<int>::const_iterator ptr1;
    for (ptr1 = items.begin(); ptr1 != items.end(); ++ptr1) { 
        cout << *ptr1 << ' ';
    }
}



//task 10 functions
/*
nonConstIteratorForPrint(const list<int>& items) {
    for (list<int>::iterator ptr : items) {
        cout << *ptr;
    }
}
*/
//don't use iterators in ranged for loop, just numbers because items holds numbers not iterators
/*
constIteratorForPrint(const list<int>& items) {
    for (list<int>::const_iterator ptr: items) {
        cout << *ptr;
    }
}
*/
constIteratorForPrint(const list<int>& items) {
    for (int num: items) {
        cout << num << ' ';
    }
}



//task 11 functions
autoForPrint(const list<int>& items) {
    for (auto item: items) {
        cout << item << ' ';
    }
}


//task 12 functions
//function will not work unless all iterators are const.
list<int>::const_iterator myFind(const list<int>& items, int findThis) {
    for (list<int>::const_iterator ptr = items.begin(); ptr != items.end(); ++ptr) {
        if (*ptr == findThis) {
            return ptr;
        }
    }
    return items.end();
}


//task 13 functions
//using auto only for the ptr because its obvious to compiler that return type of begin() method is auto
list<int>::const_iterator myAutoFind(const list<int>& items, int findThis) {
    for (auto ptr = items.begin(); ptr != items.end(); ++ptr) {
        if (*ptr == findThis) {
            return ptr;
        }
    }
    return items.end();
}

//task 15 function
bool isEven(int num) {
    return (num % 2 == 0);
}

//task 19 function
//this find will take start and end and value. Not like other finds where it tkaes the vector/array
list<int>::const_iterator ourFind(list<int>::const_iterator start, list<int>::const_iterator stop, int findThis) {
    cout << "This is our find NON TEMPLATE VERSION" << endl;
    for (auto ptr = start; ptr != stop; ++ptr) {
        if (*ptr == findThis) {
            return ptr;
        }
    }
    return stop;
}


//task 20 function
template<typename T, typename U>
T ourFind(const T& start, const T& stop, const U& findThis) {
    cout << "This is our find TEMPLATE VERSION" << endl;
    for (T ptr = start; ptr != stop; ++ptr) {
        if (*ptr == findThis) {
            return ptr;
        }
    return stop;
    }
}



//#####################################################################################



int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";

    vector<int> Vector{1, 3, 2, 4};
    for (int num: Vector) {
        cout << num << ' ';
    }

    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";

    list<int> List(Vector.begin(), Vector.end());   //using constructor that takes begin() and end()

    for (int num: Vector) {
        cout << num << ' ';
    }

    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";

    //sort(Vector);
    sort(Vector.begin(), Vector.end());
    //sort(List.begin(), List.end());       sorting a list in this way does NOT work
    for (int num: Vector) {
        cout << num << ' ';
    }

    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";

    for (size_t i = 0; i < Vector.size(); i+=2) {
        cout << Vector[i] << ' ';
    }

    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the same technique.
    cout << "Task 5:\n";

    //for (size_t i = 0; i < List.size(); i+=2) {
    //    cout << List[i] << ' ';       //no match for operator[].    
    //}      
    //function would take N^2/2 time since list does not have random access. Finding would always start from
    //the beginning

    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";

    vector<int>::iterator ptr; 
    for (ptr = Vector.begin(); ptr != Vector.end(); ptr += 2) {
        cout << *ptr << ' ';
    }

    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump the iterator as in task 6.
    cout << "Task 7:\n";

    list<int>::iterator ptr1;
    for (ptr1 = List.begin(); ptr1 != List.end(); ++ ++ptr1) {  //use overloaded increment operator
        //need to add twice. ++ ++ptr1 does that.
        cout << *ptr1 << ' ';
    }


    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";

    List.sort();  //use list's sort method that takes no arguement
    for (ptr1 = List.begin(); ptr1 != List.end(); ++ptr1) {
        cout << *ptr1 << ' ';
    }

    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";

    //nonConstIteratorPrint(List);
    //writing a function that does NOT use const iterator, when list is passed as const, will compile error
    constIteratorPrint(List);

    cout << "\n=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";

    //nonConstIteratorForPrint(List);
    constIteratorForPrint(List);

    cout << "\n=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate items in the list
    cout << "Task 11:\n";

    cout << autoForPrint(List) << endl;

    cout << "\n=======\n";
    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";

    auto save1 = myFind(List, 3);
    if (save1 != List.end()) {
        cout << *save1 << endl;
    }
    //iterators must all be const since passed in as const

    cout << "\n=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";

    auto save_7 = myAutoFind(List, 3);
    if (save_7 != List.end()) {
        cout << *save_7 << endl;
    }


    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";

    auto save = find(List.begin(), List.end(), 3);
    if (save != List.end()) {
        cout << *save;
    }

    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";

    auto save_6 =find_if(List.begin(), List.end(), isEven);
    if (save_6 != List.end()) {
        cout << *save_6;
    }

    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";

    struct Functor {
        bool operator()(int n) {return n % 2 == 0; }
    };
    Functor functor;
    auto save_5 = find_if(List.begin(), List.end(), functor);
    if (save_5 != List.end()) {
        cout << *save_5;
    }

    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";

    [] { cout << "Hello Lambda!"; }();
    [] (int a, int b) { cout << a + b << endl; } (4, 5);
    int result = [] (int a, int b) { return a + b; } (4, 5);    //notice no return type, obvious to compiler
    cout << "the result is: " << result << endl;
    auto save_4 = find_if(List.begin(), List.end(), [] (int n) {return n % 2 ==0;});
    if (save_4 != List.end()) {
        cout << *save_4 << endl;
    }
    
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";

    int arr[4]; 

    copy(Vector.begin(), Vector.end(), arr);    //how does this work when you don't pass in a arr.begin() or 
    //an iterator on the first place to copy in arr?

    //for (int item: arr) {
    //    cout << item << ' ';
    //}
    //arrays can't use for ranged loop becuase no iterators and no begin or end

    for (size_t i =0; i < sizeof(arr)/sizeof(arr[0]); ++i) {
        cout << arr[i] << ' ';
    }


    cout << "\n=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";

    auto save_2 = ourFind(List.begin(), List.end(), 3);
    if (save_2 != List.end()) {
        cout << *save_2;
    }

    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";

    auto save_3 = ourFind(Vector.begin(), Vector.end(), 3);
    if (save_3 != Vector.end()) {
        cout << *save_3;
    }


    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing 
    cout << "Task 21:\n";

    //vector of strings to keep track
    vector<string> words; 
    std::ifstream ifs("pooh-nopunc.txt");
	if (!ifs) {
		std::cerr << "Could not open file.\n";
		exit(1);
	}
    string word;
    while (ifs >> word) {
        //insert if not present
        if (find(words.begin(), words.end(), word) == words.end()) {
            words.push_back(word);
        }
    }
    for (const string& temp_word_1 : words) {
        cout << temp_word_1 << ' ';
    }

    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";

    set<string> set_words;
    std::ifstream ifs2("pooh-nopunc.txt");
	if (!ifs2) {
		std::cerr << "Could not open file.\n";
		exit(1);
	}
    string set_word;
    while (ifs2 >> set_word) {
        //insert will insert if not existing already. So just insert
        set_words.insert(set_word);
    }
    for (const string& temp_word_1 : set_words) {
        cout << temp_word_1 << ' ';
    }

    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";

    map<string, vector<int>> wordMap;
    std::ifstream ifs3("pooh-nopunc.txt");
	if (!ifs3) {
		std::cerr << "Could not open file.\n";
		exit(1);
	}
    string map_word;
    int index = 0;
    while (ifs3 >> map_word) {

//create a new word and empty vector if that word doesnt exist. If it does exist, it will just go to it and 
//add to index. 
        wordMap[map_word].push_back(index);
        ++index;
    }
    
    for (const auto& item : wordMap) {
        //print out the word
        cout << item.first << ' ';
        //print out all indices that it appears
        for (size_t i =0; i < item.second.size(); ++i) {
            cout << item.second[i] << ' ';
        }
        cout << ' ';
    }

    cout << "=======\n";
}