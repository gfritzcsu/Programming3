//============================================================================
// -------------------------------------------
// Program Name: C++ Reversal
// Author: Greg Fritz
// Professor Herbert Pensado
// CSC-450-1 Programming 3
// Date: January 18, 2026
// -------------------------------------------
//============================================================================
// Pseudocode:
//BEGIN PROGRAM
//
//DECLARE string userInput
//DECLARE string fileContents
//
//PROMPT user to enter text
//READ userInput
//
//OPEN CSC450_CT5_mod5.txt in append mode
//WRITE userInput to file
//CLOSE file
//
//OPEN CSC450_CT5_mod5.txt in read mode
//READ entire contents into fileContents
//CLOSE file
//
//CALL reverseText(fileContents)
//STORE result in reversedText
//
//OPEN CSC450-mod5-reverse.txt in write mode
//WRITE reversedText to file
//CLOSE file
//
//DISPLAY success messages
//
//END PROGRAM
//
//
//FUNCTION reverseText(inputText)
//    REVERSE characters in inputText
//    RETURN reversed string
//END FUNCTION

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// Function to reverse all characters in a string
string reverseText(const string& text) {
    string reversed = text;
    reverse(reversed.begin(), reversed.end());
    return reversed;
}

int main() {
    string userInput;
    string fileContents;
    string line;

    // Prompt user for input
    cout << "Enter text to append to CSC450_CT5_mod5.txt:\n";
    getline(cin, userInput);

    // Append user input to existing file
    ofstream outFile("CSC450_CT5_mod5.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file for appending.\n";
        return 1;
    }

    outFile << userInput << endl;
    outFile.close();

    // Read entire file contents
    ifstream inFile("CSC450_CT5_mod5.txt");
    if (!inFile) {
        cerr << "Error opening file for reading.\n";
        return 1;
    }

    while (getline(inFile, line)) {
        fileContents += line + "\n";
    }
    inFile.close();

    // Reverse file contents
    string reversedText = reverseText(fileContents);

    // Write reversed content to new file
    ofstream reverseFile("CSC450-mod5-reverse.txt");
    if (!reverseFile) {
        cerr << "Error creating reverse file.\n";
        return 1;
    }

    reverseFile << reversedText;
    reverseFile.close();

    cout << "\nData appended successfully.";
    cout << "\nReversed file created: CSC450-mod5-reverse.txt\n";

    return 0;
}
