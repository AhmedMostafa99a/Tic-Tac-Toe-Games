#ifndef VALIDATION_H
#define VALIDATION_H

#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cstdint>
#include <iomanip>
#include <limits>
#include <regex>
#include <thread>
#include <chrono>

// Colors Format for console output
#define RESET "\033[0m"
#define BLACK "\033[30m"   /* Black */
#define RED "\033[31m"     /* Red */
#define GREEN "\033[32m"   /* Green */
#define YELLOW "\033[33m"  /* Yellow */
#define BLUE "\033[34m"    /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m"    /* Cyan */
#define WHITE "\033[37m"   /* White */

// Bold and underline text formats
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define SEPARATE cout << MAGENTA << setw(50) << setfill('-') << "" << RESET << endl;

using namespace std;

class Validation
{
public:
    friend bool isValidChoice(const int &, const int &, const int &, const string &ErrorMsg);
    friend bool isValidMove(const int &, const int &, const string &ErrorMsg);
    friend bool isValidFileName(const string &email, const string &msg);
    // bool isValidUsername(const string &username, const string &msg);
};

bool isValidChoice(const int &choice, const int &LowerLim, const int &UpperLim, const string &ErrorMsg)
{
    // Validate the user's input
    if (cin.fail() || choice < LowerLim || choice > UpperLim)
    {
        cin.clear();                                         // Clear input error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        cerr << BOLD << RED << endl
             << ErrorMsg << RESET;
        return false;
    }

    return true;
}

bool isValidMove(const int &x, const int &y, const string &ErrorMsg)
{
    // Validate the user's input
    if (cin.fail() || x < 1 || x > 3 || y < 1 || y > 3)
    {
        cin.clear();                                         // Clear input error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        cerr << BOLD << RED << endl
             << ErrorMsg << RESET;
        return false;
    }

    return true;
}

bool isValidFileName(const string &file, const string &msg)
{
    // Input validation: Ensure file name is in valid format
    regex correct_file(R"(^[a-zA-Z0-9_\-]+\.txt$)");
    if (!regex_match(file, correct_file))
    {
        cout << BOLD << RED << "Invalid filename." << RESET << " Make sure it ends with .txt and contains only alphanumeric characters, underscores, or hyphens.\n"
             << endl
             << endl;

        return false;
    }

    return true;
}

// vector<string> MainUI::inputInstruction()
// {
//     int size;
//     string instruction;
//     vector<string> instructions;

//     cout << BOLD << "Enter the number of instructions to input (maximum 123): " << RESET;

//     cin >> size;

//     // Validate the number of instructions
//     while (cin.fail() || size > 123 || size < 0)
//     {
//         cin.clear();                                         // Clear input error flag
//         cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input

//         cerr << BOLD << RED << "\nInvalid input. Please enter a number between 0 and 123: " << RESET;
//         cin >> size;
//     }

//     cout << "Now enter the instructions line by line, where each line is a 4 digits hexa number: ";

//     cin.clear();                                         // Clear any error flags
//     cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore characters until a newline is found

//     // Read the instructions from the user
//     for (int i = 0; i < size; i++)
//     {
//         getline(cin, instruction); // Read the next line of input

//         // Validate the instruction format
//         regex correct_instruction(R"(^[0-9A-Fa-f]{4}$)");
//         while (!regex_match(instruction, correct_instruction))
//         {
//             cout << BOLD << RED << "Invalid instruction." << RESET << " Each instruction must be a 4-digit hexadecimal number (0-9, A-F).\n"
//                  << endl;
//             cout << "Please re-enter the instruction: ";
//             getline(cin, instruction);
//         }

//         transform(instruction.begin(), instruction.end(), instruction.begin(), ::toupper);
//         instructions.push_back(instruction); // Store the instruction
//     }
//     return instructions;
// }
#endif // VALIDATION_H