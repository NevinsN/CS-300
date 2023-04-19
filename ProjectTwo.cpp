//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Nicholas Nevins
// Version     : 1.0
// Copyright   : Copyright © 2023, format courtesy SNHU assignments
// Description : Handle ABCU Course Lists in a Data Structure
//============================================================================

#include <iostream>
#include <time.h>
#include <fstream>
#include <limits>
#include <vector>
#include <sstream>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a structure to hold course information
struct Course {
    string CourseID; // unique identifier
    string CourseDescription;
    vector<string> CoursePrerequisites;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void printInOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void PrintInOrder();
    void InsertCourse(Course course);
    Course FindCourse(string courseId);
    void PrintCourse();
    vector<vector<string>> ParseCSVtoVector(string csvPath);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
    // root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node

}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::PrintInOrder() {
    // In order root
    // call printInOrder fuction and pass root 
    printInOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::InsertCourse(Course course) {
    // Implement inserting a course into the tree
    // if root equal to null ptr
    if (root == nullptr) {
        // root is equal to new node bid
        root = new Node(course);
    }
    // else
    else {
        // add Node root and bid
        this->addNode(root, course);
    }
}

/**
 * Searches for a single course by CourseID
 */
Course BinarySearchTree::FindCourse(string courseID) {
    // Implement searching the tree for a course
    // set current node equal to root
    Node* currentNode = root;

    // keep looping downwards until bottom reached or matching courseID found
    while (currentNode != nullptr) {
        // if match found, return current course
        if (currentNode->course.CourseID.compare(courseID) == 0) {
            return currentNode->course;
        }
        // if course is smaller than current node then traverse left
        if (courseID.compare(currentNode->course.CourseID) < 0) {
            currentNode = currentNode->left;
        }
        // else larger so traverse right
        else {
            currentNode = currentNode->right;
        }
    }

    Course course;
    return course;
}

/**
 * Prints a single course from user input
 */
void BinarySearchTree::PrintCourse() {
    string userInput;
    Course courseToPrint;

    cout << "Which course do you want to know about? ";
    cin >> userInput;

    courseToPrint = FindCourse(userInput);

    // Checks if a course was returned by FindCourse method
    // If it was, print that course
    if (courseToPrint.CourseID.compare(userInput) == 0) {
        //output CourseID, CourseDescription
        cout << endl << courseToPrint.CourseID
            << ", " << courseToPrint.CourseDescription
            << endl;
        cout << "Prerequisites: ";
        for (unsigned int i = 0; i < courseToPrint.CoursePrerequisites.size(); i++) {
            if (courseToPrint.CoursePrerequisites[i] == "") {
                cout << "None\n" << endl;
            }
            else {
                cout << courseToPrint.CoursePrerequisites[i];
            }
            
            if (i + 1 != courseToPrint.CoursePrerequisites.size()) {
                cout << ", ";
            }
            else {
                cout << endl << endl;
            }
        }
    }
    // If there was no course returned, return error
    else {
        cout << "\nCourse " << userInput << " not found.\n" << endl;
    }
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // Implement inserting a course into the tree
    // if node is larger then add to left
    if (node->course.CourseID.compare(course.CourseID) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }
        // else recurse down the left node
        else {
            this->addNode(node->left, course);
        }
    }
    // else
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
        }
        //else
        else {
            // recurse down the left node
            this->addNode(node->right, course);
        }
    }
}

void BinarySearchTree::printInOrder(Node* node) {
    // Pre order root
    // if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder not left
        printInOrder(node->left);

        //output CourseID, CourseDescription
        cout << node->course.CourseID
            << ", " << node->course.CourseDescription
            << endl;

        //InOder right
        printInOrder(node->right);
    }
}

/**
 * Load a CSV file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the courses read
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {
    unsigned int courseCount = 0; // tracks how many courses are loaded by the method
    vector<vector<string>> parsedCSV;

    cout << "\nLoading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    parsedCSV = bst->ParseCSVtoVector(csvPath);

    // This is a tracker to handle when courses are not loaded due to missing prerequisites.
    // 25 is plenty large for this purpose, but the amount might need to be adjusted for a larger, more live launch scenario
    int repeatTracker = 25;

    // while loop that will run through parsedCSV vector until it is empty
    while (!parsedCSV.empty()) {

        // Create a data structure and add to the collection of courses
        Course course;
        course.CourseID = parsedCSV[0][0];
        course.CourseDescription = parsedCSV[0][1];
        course.CoursePrerequisites.clear();

        // for loop that fills in the prereqs
        // j starts at 2 since that should be the first index a prereq can be possible
        for (unsigned int i = 2; i < parsedCSV[0].size(); i++) {
            course.CoursePrerequisites.push_back(parsedCSV[0][i]);
        }

        // This is a simple statement that checks if the next course has already been added, then skips it if it has
        // Put in as a failsafe against hiccups
        if (course.CourseID.compare(bst->FindCourse(course.CourseID).CourseID) == 0) { break; }

        // Checks if a course has no prerequisits (as denoted by the empty first element) and adds it to the BST
        if (course.CoursePrerequisites[0] == "") {
            // push this course to the end
            bst->InsertCourse(course);
            
            // iterate courseCount            
            ++courseCount; 

            // deletes the first element from parsedCSV
            parsedCSV.erase(parsedCSV.begin()); 

            // resets the repeatTracker to evaluate the next courses
            repeatTracker = 25; 
            
            // takes us back to the top of the while loop and the next course
            continue; 
        }

        // for loop that iterates through course's prerequisites and checks if they're in the bst
        for (unsigned int i = 0; i < course.CoursePrerequisites.size(); i++) {
            // checks if the [i] prerequisite for course is in the bst and if there are more prerequisits to check
            // if it is not the last found prerequisit, it will continue to the next iteration
            if (course.CoursePrerequisites[i].compare(bst->FindCourse(course.CoursePrerequisites[i]).CourseID) == 0 
                && i < course.CoursePrerequisites.size() - 1) {
                continue;
            }
            // checks if the [i] prerequisite for course is in the bst and if there are no more prerequisits to check
            // if it is the last found prerequisit, it will add course to the bst and remove it from the vector
            else if (course.CoursePrerequisites[i].compare(bst->FindCourse(course.CoursePrerequisites[i]).CourseID) == 0
                     && i >= course.CoursePrerequisites.size() - 1) {
                // push this course to the end
                bst->InsertCourse(course);
                
                // iterate courseCount
                ++courseCount; 

                // deletes the first element from parsedCSV
                parsedCSV.erase(parsedCSV.begin());

                // resets the repeatTracker to evaluate the next courses
                repeatTracker = 25;
                break;
            }
            // if at least one prerequisite is not found in the bst, this will handle that
            // it will either reject the course for missing prerequisites, 
            // or it will shift the course to the end of the vector and decrement repeatTracker
            else {
                // checks if repeatTracker is above zero
                // the reasoning is that if repeat tracker reaches 0, 
                // it has run through enough available courses that the prerequisites must not exist.
                if (repeatTracker <= 0) {
                    // prints error message than removes the course from the vector
                    cout << "\nCannot locate prerequisite for course " << course.CourseID << ". Cannot load course.\n" << endl;
                    parsedCSV.erase(parsedCSV.begin());

                    // breaks to avoid the next snippet of code
                    break;
                }
                
                // body of code used to rotate the first item to the back of the vector
                // creates a copy of current cours to push_back after the deletion
                vector<string> temp = parsedCSV[0];

                // deletes the current course
                parsedCSV.erase(parsedCSV.begin());

                // adds temp back into the vector at the end
                parsedCSV.push_back(temp);

                // clears temp
                temp.clear();

                // decrements repeatTracker
                --repeatTracker;

                // breaks to the top of the while loop
                break;
            }
        }
    }

    // prints the courseCount for loaded courses. If statement to use proper plurals
    if (courseCount == 1) {
        cout << courseCount << " course loaded." << endl;
    }
    else { cout << courseCount << " courses loaded." << endl; }
}


//============================================================================
// Method used for Parsing
//============================================================================
vector<vector<string>> BinarySearchTree::ParseCSVtoVector(string csvPath) {
    vector<string> parsedCourse;
    vector<vector<string>> parsedCourseFile;
    string parsedLine;
    fstream CSVtoParse(csvPath);

    while (getline (CSVtoParse, parsedLine)) {
        string parsedPhrase;
        stringstream lineToSplit;
        lineToSplit << parsedLine;

        while (getline (lineToSplit, parsedPhrase, ',')) {
            parsedCourse.push_back(parsedPhrase);
        }
        parsedCourseFile.push_back(parsedCourse);
        parsedCourse.clear();

    }
    return parsedCourseFile;
}

/**
 * main() method, beause we all gotta have one
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    int choice = 0;
    while (choice != 9) {
        cout << "Welcome to the course planner." << endl;
        cout << "\n  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit\n" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        while (!cin.good())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {

        case 1:

            // Initialize a timer variable before loading bids
            ticks = clock();

            if (csvPath == "") {
                // get user's input for the file path
                cout << "Please enter full file path: ";
                cin >> csvPath;
            }

            // Complete the method call to load the courses
            //loadCourses(csvPath, bst);
            loadCourses(csvPath, bst);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->PrintInOrder();
            break;

        case 3:
            ticks = clock();

            bst->PrintCourse();

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds\n" << endl;

            break;
        default:
            cout << "Invalid selection. Try again." << endl;
            break;
        }   
    }

    cout << "Good bye." << endl;

    return 0;
}
