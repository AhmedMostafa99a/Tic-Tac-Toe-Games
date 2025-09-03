#include <iostream>
#include <vector>
#include <iomanip>
#include <set>
#include <algorithm>
#include <tuple>
#include "BoardGame_Classes.h"
#include "Validation.h"

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
#define INDICATOR BOLD << BLACK << ">> " << RESET

using namespace std;

class Numerical_Board : public Board<int>
{
private:
    vector<vector<int>> board;

public:
    vector<int> pl1_available_choices{1, 3, 5, 7, 9};
    vector<int> pl2_available_choices{2, 4, 6, 8};
    Numerical_Board();
    ~Numerical_Board();
    void display_board();
    int getN_moves();
    int MiniMax(int &x, int &y, int &value, int alpha, int beta, bool isMaximizing, bool isfirst);
    int check_status();
    const vector<int> &getPl1Choices()
    {
        return pl1_available_choices;
    };
    const vector<int> &getPl2Choices()
    {
        return pl2_available_choices;
    };
    bool update_board(int x, int y, int symbol)
    {

        if (!(x < 1 || x > rows || y < 1 || y > columns) && (board[x - 1][y - 1] == 0 && symbol != 0))
        {
            if (n_moves % 2 == 0)
            {
                auto pl2_it = find(pl2_available_choices.begin(), pl2_available_choices.end(), symbol);

                if (pl2_it != pl2_available_choices.end())
                {
                    board[x - 1][y - 1] = symbol;
                    pl2_available_choices.erase(pl2_it);
                    n_moves--;
                    return true;
                }
            }
            else
            {
                auto pl1_it = find(pl1_available_choices.begin(), pl1_available_choices.end(), symbol);

                if (pl1_it != pl1_available_choices.end())
                {
                    board[x - 1][y - 1] = symbol;
                    pl1_available_choices.erase(pl1_it);
                    n_moves--;
                    return true;
                }
            }
        }

        return false;
    };

    /// Returns true if there is any winner
    bool is_win()
    {

        for (int i = 0; i < rows; i++)
        {
            if ((board[i][0] + board[i][1] + board[i][2] == 15 && board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0) ||
                (board[0][i] + board[1][i] + board[2][i] == 15 && board[0][i] != 0 && board[1][i] != 0 && board[2][i] != 0))
            {

                return true;
            }
        }

        if ((board[0][0] + board[1][1] + board[2][2] == 15 && board[0][0] != 0 && board[1][1] != 0 && board[2][2] != 0) ||
            (board[0][2] + board[1][1] + board[2][0] == 15 && board[0][2] != 0 && board[1][1] != 0 && board[2][0] != 0))
        {

            return true;
        }

        return false;
    };

    /// Return true if all moves are done and no winner
    bool is_draw()
    {

        if (n_moves == 0 && is_win() == false)
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

void Numerical_Board::display_board()
{
    cout << GREEN << BOLD << "   " << 1 << "   " << 2 << "   " << 3 << RESET << endl;
    cout << GREEN << BOLD << 1 << RESET << "  " << board[0][0] << BOLD << " | " << RESET << board[0][1] << BOLD << " | " << RESET << board[0][2] << endl
         << "   " << setw(9) << setfill('-') << "" << endl
         << GREEN << BOLD << 2 << RESET << "  " << board[1][0] << BOLD << " | " << RESET << board[1][1] << BOLD << " | " << RESET << board[1][2] << endl
         << "   " << setw(9) << setfill('-') << "" << endl
         << GREEN << BOLD << 3 << RESET << "  " << board[2][0] << BOLD << " | " << RESET << board[2][1] << BOLD << " | " << RESET << board[2][2] << endl;

    cout << endl;
}

Numerical_Board::Numerical_Board()
{
    board.resize(3);
    for (int i = 0; i < board.size(); i++)
    {
        board[i].resize(3, 0);
    }

    rows = 3;
    columns = 3;
    n_moves = 9;
}

Numerical_Board::~Numerical_Board()
{
}

int Numerical_Board::getN_moves()
{
    return n_moves;
}

int Numerical_Board::check_status()
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

int Numerical_Board::MiniMax(int &x, int &y, int &value, int alpha, int beta, bool isMaximizing, bool isfirst)
{
    int res = check_status();
    if (res != 1)
    {
        return res;
    }

    int max_score = INT_MIN, min_score = INT_MAX;
    int finalX, finalY, finalValue;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
            {

                if (isMaximizing)
                {
                    for (int k = 0; k < pl1_available_choices.size(); k++)
                    {
                        board[i][j] = pl1_available_choices[k];
                        int score = MiniMax(x, y, value, alpha, beta, false, false);
                        board[i][j] = 0;

                        if (score >= max_score)
                        {

                            max_score = score;
                            finalX = i;
                            finalY = j;
                            finalValue = pl1_available_choices[k];
                        }

                        if (isfirst)
                            cout << "in " << i << ", " << j << (score == 2 ? " Player1 wins" : (score == -2) ? "Player 2 wins"
                                                                                                             : " Draw");
                        alpha = max(alpha, score);

                        if (beta <= alpha)
                        {
                            break;
                        }
                    }
                }
                else
                {

                    for (int f = 0; f < pl2_available_choices.size(); f++)
                    {
                        board[i][j] = pl2_available_choices[f];
                        int score = MiniMax(x, y, value, alpha, beta, true, false);
                        board[i][j] = 0;

                        if (score >= max_score)
                        {

                            max_score = score;
                            finalX = i;
                            finalY = j;
                            finalValue = pl2_available_choices[f];
                        }

                        if (isfirst)
                        {
                            cout << "in " << i << ", " << j << (score == 2 ? " Player1 wins" : (score == -2) ? "Player 2 wins"
                                                                                                             : " Draw");
                        }
                        beta = min(beta, score);

                        if (beta <= alpha)
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
    if (isfirst)
    {

        x = finalX;
        y = finalY;
        value = finalValue;
    }

    return (isMaximizing ? max_score : min_score);
}

///////////////////////////////////////////////////////
// Player Class

class Nume_Player : public Player<int>
{
private:
    Numerical_Board *Num_board_ptr;

public:
    Nume_Player(string, int);
    friend ostream &operator<<(ostream &, const vector<int> &);
    void getmove(int &, int &);
    int getsymbol();
};

Nume_Player::Nume_Player(string name, int symbol) : Player<int>(name, symbol)
{
    Num_board_ptr = (Numerical_Board *)boardPtr;
};

ostream &operator<<(ostream &os, const vector<int> &vec)
{
    os << BOLD << GREEN << "[" << RESET;

    if (vec.size() != 0)
    {
        for (int i = 0; i < vec.size() - 1; i++)
        {
            os << CYAN << vec[i] << RESET << ", ";
        }
    }

    os << CYAN << vec[vec.size() - 1] << RESET << BOLD << GREEN << "]" << RESET;

    return os;
}

void Nume_Player::getmove(int &x, int &y)
{

    cout << INDICATOR "Enter your move coordinates (x,y) (1 to 3) respectively seperated by a space: ";
    cin >> x >> y;

    while (!isValidMove(x, y, "Invalid coordinates, please make sure that both x and y are between (1 to 3) and seperated by space: "))
    {
        cin >> x >> y;
    }

    symbol = getsymbol();
}

int Nume_Player::getsymbol()
{
    vector<int> print;
    Num_board_ptr = (Numerical_Board *)boardPtr;

    if (Num_board_ptr->getN_moves() % 2 == 0)
    {
        print = Num_board_ptr->getPl2Choices();
    }
    else
    {
        print = Num_board_ptr->getPl1Choices();
    }
    cout << INDICATOR "Now choose a number from this list " << print << ": ";

    cin >> symbol;

    return symbol;
}

////////////////////////////////////////////////////////////
// Random Player Class

class Nume_Random_Player : public Player<int>
{
private:
    int dimension = 3;
    Numerical_Board *Ran_board_ptr;

public:
    Nume_Random_Player(string, int);
    void getmove(int &, int &);
    int getsymbol()
    {
        Ran_board_ptr = (Numerical_Board *)boardPtr;

        if (Ran_board_ptr->getN_moves() % 2 != 0)
        {
            do
            {
                symbol = rand() % 9;
            } while (symbol % 2 == 0 && symbol != 0);
        }
        else
        {
            do
            {
                symbol = rand() % 9;
            } while (symbol % 2 != 0 && symbol != 0);
        }

        return symbol;
    }
};

Nume_Random_Player::Nume_Random_Player(string name, int symbol) : Player<int>(name, symbol)
{

    this->dimension = 4;
    this->name = name;
    Ran_board_ptr = (Numerical_Board *)boardPtr;
    srand(static_cast<unsigned int>(time(0)));
};
void Nume_Random_Player::getmove(int &x, int &y)
{

    x = rand() % this->dimension + 1;
    y = rand() % this->dimension + 1;
    symbol = getsymbol();
}

////////////////////////////////////////////////////////////////////////////////////
// MiniMax Player Class

class MiniMax_Player : public Player<int>
{
private:
    int value = 0;
    Numerical_Board *numerical_board;

public:
    MiniMax_Player();
    void getmove(int &x, int &y);
    tuple<int, int, int> getBestMove();
};

MiniMax_Player::MiniMax_Player() : Player<int>(symbol)
{
    this->name = "AI Player";
    this->symbol = 0;
    numerical_board = new Numerical_Board;
}

void MiniMax_Player::getmove(int &x, int &y)
{

    tuple<int, int, int> bestMove = getBestMove();
    x = get<0>(bestMove);
    y = get<1>(bestMove);
    value = get<2>(bestMove);
}

tuple<int, int, int> MiniMax_Player::getBestMove()
{
    tuple<int, int, int> bestMove = {0, 0, 0};

    for (int i = 1; i < 4; ++i)
    {
        for (int j = 1; j < 4; ++j)
        {
            for (int k = 0; k < numerical_board->pl1_available_choices.size(); k++)
            {

                if (this->boardPtr->update_board(i, j, numerical_board->pl1_available_choices[k]))
                {
                    if (this->boardPtr->is_win())
                    {
                        int moveValue = numerical_board->MiniMax(i, j, numerical_board->pl1_available_choices[k], INT_MIN, INT_MAX, true, true);
                        this->boardPtr->update_board(i, j, 0);                        // Undo move
                        bestMove = {i, j, numerical_board->pl1_available_choices[k]}; // Winning move found
                    }
                    this->boardPtr->update_board(i, j, 0); // Undo move
                }
            }
        }
    }

    return bestMove;
}

void playNumerical()
{
    int choice;
    Player<int> *players[2];
    Numerical_Board *B = new Numerical_Board;
    string pl1, pl2;

    cout << BOLD << GREEN << "Welcome to FCAI Numerical Tic_Tac_Toe Game" << RESET << endl;
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
        players[0] = new Nume_Player(pl1, 0);
        break;
    case 2:
        players[0] = new Nume_Random_Player(pl1, 0);
        break;
    case 3:
        players[0] = new MiniMax_Player();
        players[0]->setBoard(B);
        break;
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
        players[1] = new Nume_Player(pl2, 0);
        break;
    case 2:
        players[1] = new Nume_Random_Player(pl2, 0);
        break;
    case 3:
        players[1] = new MiniMax_Player();
        players[1]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    // Create the game manager and run the game
    players[0]->setBoard(B);
    players[1]->setBoard(B);
    GameManager<int> Numerical_game(B, players);
    Numerical_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
}