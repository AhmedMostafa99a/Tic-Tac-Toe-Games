// #include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "MisereTicTacToe.h"
#include "TicTacToe5x5.h"
#include "AIplayer.h"
#include "ultimate_board.h"
#include "Word_XO.h"
#include "Triangle_XO.h"
#include "SUS_XO.h"
#include "Connect4.h"
#include "Numerical_Tic_Tac_Toe.h"
#include "Validation.h"

using namespace std;

int main()
{
    while (true)
    {

        int ch;
        cout << BOLD << GREEN << "Welcome to FCAI Tic-Tac-Toe Game. :)\n"
             << RESET;
        cout << "Enter the number of the game you want to play\n";
        cout << "[1] pyramid Tic tac toe game\n";
        cout << "[2] Connect Four game\n";
        cout << "[3] Tic tac toe 5x5 game\n";
        cout << "[4] Word Tic tac toe game\n";
        cout << "[5] Numerical Tic tac toe game\n";
        cout << "[6] Misere Tic tac toe game\n";
        cout << "[7] Ultimate Tic tac toe game\n";
        cout << "[8] SUS Tic tac toe game\n";
        cout << "[9] Exit\n";
        cout << INDICATOR BOLD << "Choice: " << RESET;
        cin >> ch;

        while (!isValidChoice(ch, 1, 9, "Invalid Choice, choose a number between 1 - 9: "))
        {
            cin >> ch;
        }

        switch (ch)
        {
        case 1:
            Triangle_XO game1;
            game1.start_Triangle_XO();
            break;

        case 2:
            playConnect4();
            break;

        case 3:
            playTicTacToe5x5();
            break;
        case 4:
            Word_XO game2;
            game2.start_Triangle_XO();
            break;
        case 5:
            playNumerical();
            break;
        case 6:
            playMisereTicTacToe();
            break;
        case 7:
            playUltimate();
            break;
        case 8:
            SUS_XO game3;
            game3.start_SUS_XO();
            break;

        case 9:
            cout << "See you later, hope you had a good time. Exiting now" << std::endl;
            break;

        default:
            continue;
        }
    }

    return 0;
}
