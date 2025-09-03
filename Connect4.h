#include <iostream>
#include <vector>
#include <iomanip>
#include <set>
#include <algorithm>
#include <tuple>
#include <map>
#include "Validation.h"
#include "BoardGame_Classes.h"

#define INDICATOR BOLD << BLACK << ">> " << RESET

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

class Connect4 : public Board<char>
{
private:
    vector<vector<char>> board;
    map<int, int> howFull;

public:
    Connect4();
    void display_board();
    int getN_moves();
    // int MiniMax(int &x, int &y, int &value, int alpha, int beta, bool isMaximizing, bool isfirst);
    int check_status();
    map<int, int> &getHowFull();
    bool update_board(int x, int y, char symbol)
    {

        if (howFull[x] < 6 && (board[5 - howFull[x]][x - 1] == ' ') && symbol == 'X')
        {

            board[5 - howFull[x]][x - 1] = symbol;
            howFull[x]++;
            n_moves++;
            return true;
        }
        else if (howFull[x] < 6 && (board[5 - howFull[x]][x - 1] == ' ') && symbol == 'O')
        {

            board[5 - howFull[x]][x - 1] = symbol;
            howFull[x]++;
            n_moves++;
            return true;
        }
        return false;
    }

    /// Returns true if there is any winner
    bool is_win()
    {

        int counter = 0;
        for (int i = 0; i < rows; i++)
        {
            counter = 0;
            for (int j = 0; j < columns; j++)
            {

                if (j == 0)
                {
                    if (board[i][j] != ' ')
                    {
                        counter++;
                    }
                    else
                    {
                        continue;
                    }
                }
                else if (board[i][j] != ' ' && counter == 0)
                {
                    counter++;
                }
                else if (board[i][j] == board[i][j - 1] && board[i][j] != ' ')
                {
                    counter++;
                    if (counter == 4)
                    {
                        return true;
                    }
                }
                else
                {
                    counter = 0;
                }
            }
        }

        counter = 0;

        for (int k = 0; k < columns; k++)
        {
            counter = 0;
            for (int f = 0; f < rows; f++)
            {

                if (f == 0)
                {

                    if (board[f][k] != ' ')
                    {
                        counter++;
                    }
                    else
                    {
                        continue;
                    }
                }
                else if (board[f][k] != ' ' && counter == 0)
                {
                    counter++;
                }
                else if (board[f][k] == board[f - 1][k] && board[f][k] != ' ')
                {
                    counter++;
                    if (counter == 4)
                    {
                        return true;
                    }
                }
                else
                {
                    counter = 0;
                }
            }
        }

        for (int i = 0; i < rows - 3; i++)
        {
            counter = 0;
            for (int j = 0; j < columns - 3; j++)
            {
                if (board[i][j] != ' ' && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] == board[i + 3][j + 3])
                {

                    return true;
                }
            }
        }

        for (int i = 3; i < rows; i++)
        {
            counter = 0;
            for (int j = 0; j < columns - 3; j++)
            {
                if (board[i][j] != ' ' && board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i - 2][j + 2] && board[i][j] == board[i - 3][j + 3])
                {

                    return true;
                }
            }
        }

        return false;
    };

    /// Return true if all moves are done and no winner
    bool is_draw()
    {

        if (n_moves == 42 && is_win() == false)
        {
            return true;
        }

        return false;
    };

    /// Return true if the game is over
    bool game_is_over()
    {
        return is_win() || is_draw();
    };
};

void Connect4::display_board()
{
    int k = 0;
    cout << GREEN << BOLD << "    " << 1 << "   " << 2 << "   " << 3 << "   " << 4 << "   " << 5 << "   " << 6 << "   " << 7 << RESET << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << GREEN << BOLD << i + 1 << RESET << "   ";

        for (int j = 0; j < columns - 1; j++)
        {
            k = j;
            cout << board[i][j] << BOLD << " | " << RESET;
        }
        cout << board[i][k + 1];
        cout << endl
             << "    " << setw(25) << setfill('-') << "" << endl;
    }

    cout << endl;
}

Connect4::Connect4()
{
    board.resize(6, vector<char>(7, ' '));

    rows = 6;
    columns = 7;
    n_moves = 0;

    for (int i = 1; i < columns + 1; i++)
    {
        howFull[i] = 0;
    }
}

map<int, int> &Connect4::getHowFull()
{

    return howFull;
}

int Connect4::getN_moves()
{
    return n_moves;
}

int Connect4::check_status()
{

    if (is_win() && (getN_moves() + 1) % 2 == 0)
    {
        return 2;
    }
    else if (is_win() && (getN_moves() + 1) % 2 != 0)
    {
        return -2;
    }
    else if (is_draw())
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
///////////////////////////////////////////////////////
// Player Class

class C4_Player : public Player<char>
{
private:
    Connect4 *c4_p;

public:
    C4_Player(string, char);
    void getmove(int &, int &);
    int getsymbol();
};

C4_Player::C4_Player(string name, char symbol) : Player<char>(name, symbol)
{

    Board<char> *p = new Connect4;
    setBoard(p);
    c4_p = (Connect4 *)boardPtr;
};

void C4_Player::getmove(int &x, int &y)
{

    cout << INDICATOR "It's " << BOLD << CYAN << name << RESET << "'s turn, please enter the number of the column you want to insert in: ";
    cin >> x;

    while (!isValidChoice(x, 1, 7, "Invalid Column number, please enter a number between (1 - 7): "))
    {
        cin >> x;
    }

    symbol = getsymbol();
}

int C4_Player::getsymbol()
{

    return symbol;
}

////////////////////////////////////////////////////////////
// Random Player Class

class C4_Random_Player : public Player<char>
{
private:
    int dimension = 7;

public:
    C4_Random_Player(string, char);
    void getmove(int &, int &);
};

C4_Random_Player::C4_Random_Player(string name, char symbol) : Player<char>(name, symbol)
{

    this->dimension = 7;
    this->name = name;
    srand(static_cast<unsigned int>(time(0)));
};
void C4_Random_Player::getmove(int &x, int &y)
{

    x = rand() % this->dimension + 1;
    symbol = getsymbol();
}

////////////////////////////////////////////////////////////////////////////////////

void playConnect4()
{
    int choice;
    Player<char> *players[2];
    Connect4 *B = new Connect4;
    string pl1, pl2;

    cout << BOLD << GREEN << "Welcome to FCAI Connect_4 Game" << RESET << endl;
    SEPARATE
    // Set up player 1
    cout << BOLD << "Enter first player name: " << RESET;
    getline(cin >> ws, pl1);
    cout << INDICATOR << BOLD << BLUE << "Choose first player type:\n"
         << RESET;
    cout << BOLD << "1. Human\n"
         << RESET;
    cout << BOLD << "2. Random Computer\n"
         << RESET;
    cout << BOLD << "3. Smart Computer (AI)\n"
         << RESET;
    cout << BOLD << "Choice: " << RESET;
    cin >> choice;

    while (!isValidChoice(choice, 1, 3, "Invalid Choice, you can only choose (1,2 or 3): "))
    {
        cin >> choice;
    };

    switch (choice)
    {
    case 1:
        players[0] = new C4_Player(pl1, 'X');
        break;
    case 2:
        players[0] = new C4_Random_Player(pl1, 'X');
        break;
    // case 3:
    //     players[0] = new MiniMax_Player();
    //     players[0]->setBoard(B);
    //     break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    cin.clear();
    cin.ignore();

    // Set up player 2
    cout << BOLD << "Enter second player name: " << RESET;
    getline(cin >> ws, pl2);
    cout << INDICATOR << BOLD << BLUE << "Choose second player type:\n"
         << RESET;
    cout << BOLD << "1. Human\n"
         << RESET;
    cout << BOLD << "2. Random Computer\n"
         << RESET;
    cout << BOLD << "3. Smart Computer (AI)\n"
         << RESET;
    cout << BOLD << "Choice: " << RESET;
    cin >> choice;

    while (!isValidChoice(choice, 1, 3, "Invalid Choice, you can only choose (1,2 or 3): "))
    {
        cin >> choice;
    };

    switch (choice)
    {
    case 1:
        players[1] = new C4_Player(pl2, 'O');
        break;
    case 2:
        players[1] = new C4_Random_Player(pl2, 'O');
        break;
    // case 3:
    //     players[1] = new MiniMax_Player();
    //     players[1]->setBoard(B);
    //     break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    // Create the game manager and run the game
    GameManager<char> Numerical_game(B, players);
    Numerical_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
}