//============================================================================
// -------------------------------------------
// Program Name: C++ Catting two strings together
// Author: Greg Fritz
// Professor Herbert Pensado
// CSC-450-1 Programming 3
// Date: December 21, 2025
// -------------------------------------------
//============================================================================
// Pseudocode:
//BEGIN PROGRAM
//
//DECLARE string input1
//DECLARE string input2
//DECLARE string combined
//DECLARE integer counter
//
//FOR counter = 1 to 3 DO
//    DISPLAY "Enter first string:"
//    READ input1
//
//    DISPLAY "Enter second string:"
//    READ input2
//
//    combined ← input1 + input2
//
//    DISPLAY "Concatenated result: " + combined
//    DISPLAY blank line
//END FOR
//
//END PROGRAM

#include <iostream>
#include <string>

using namespace std;

int main() {
    string str1, str2, result;

    // Loop to collect input three times and each time cat results after 2 inputs are received
    for (int i = 1; i <= 3; i++) {
        cout << "Iteration " << i << endl;

        cout << "Enter first string: ";
        getline(cin, str1);

        cout << "Enter second string: ";
        getline(cin, str2);

        // Concatenate strings
        result = str1 + str2;

        cout << "Concatenated result: " << result << endl;
        cout << endl;
    }

    return 0;
}
