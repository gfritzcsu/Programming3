//============================================================================
// -------------------------------------------
// Program Name: C++ Variable and Dynamic Memory Management
// Author: Greg Fritz
// Professor Herbert Pensado
// CSC-450-1 Programming 3
// Date: January 4, 2026
// -------------------------------------------
//============================================================================
// Pseudocode:
//BEGIN PROGRAM
//
//DEFINE FUNCTION getValidInteger(prompt)
//    DECLARE integer value
//    DISPLAY prompt
//    WHILE input is not a valid integer
//        DISPLAY error message
//        CLEAR input buffer
//        PROMPT again
//    END WHILE
//    RETURN value
//END FUNCTION
//
//DECLARE integer variables num1, num2, num3
//DECLARE integer pointers ptr1, ptr2, ptr3
//
//SET num1 = getValidInteger("Enter first integer: ")
//SET num2 = getValidInteger("Enter second integer: ")
//SET num3 = getValidInteger("Enter third integer: ")
//
//ALLOCATE dynamic memory for ptr1, ptr2, ptr3 using new
//
//ASSIGN values of num1, num2, num3 to pointers
//
//DISPLAY variable values
//DISPLAY pointer addresses and dereferenced values
//
//DEALLOCATE memory using delete
//
//END PROGRAM

#include <iostream>
#include <limits>
using namespace std;

// Function to get a valid integer (positive or negative)
int getValidInteger(const string& prompt) {
    int value;

    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a valid integer: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return value;
}

int main() {
    // Get validated user input
    int num1 = getValidInteger("Enter first integer: ");
    int num2 = getValidInteger("Enter second integer: ");
    int num3 = getValidInteger("Enter third integer: ");

    // Dynamically allocate memory
    int* ptr1 = new int;
    int* ptr2 = new int;
    int* ptr3 = new int;

    // Assign values to dynamic memory
    *ptr1 = num1;
    *ptr2 = num2;
    *ptr3 = num3;

    // Display variable values
    cout << "\nVariable values:" << endl;
    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;
    cout << "num3 = " << num3 << endl;

    // Display pointer addresses and values
    cout << "\nPointer details:" << endl;
    cout << "ptr1 address: " << ptr1 << " | value: " << *ptr1 << endl;
    cout << "ptr2 address: " << ptr2 << " | value: " << *ptr2 << endl;
    cout << "ptr3 address: " << ptr3 << " | value: " << *ptr3 << endl;

    // Free dynamically allocated memory
    delete ptr1;
    delete ptr2;
    delete ptr3;

    return 0;
}
