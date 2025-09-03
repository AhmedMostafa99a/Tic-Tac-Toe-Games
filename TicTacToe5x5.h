#ifndef TIC_TAC_TOE_5X5_H
#define TIC_TAC_TOE_5X5_H

#include "BoardGame_Classes.h"
#include "aiplayer.h"
#include "Validation.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <set>
#include <algorithm>
#include <tuple>
#include <limits>
#include <map>
// #include <bits/stdc++.h>

using namespace std;

template <typename T>
class TicTacToe5x5 : public Board<T>
{
public:
    TicTacToe5x5();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    void playTicTacToe5x5();

private:
    vector<vector<char>> v;
    char start = '~';
    int n_moves = 0;
    int score(const vector<vector<char>> &v, const char x);
};

template <typename T>
class tic_tac_Player : public Player<T>
{
public:
    tic_tac_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class tic_tac_Random_Player : public RandomPlayer<T>
{
protected:
    int dimension;

public:
    tic_tac_Random_Player(string Name, T symbol);
    virtual void getmove(int &x, int &y) override;
};
//======================implementation

template <typename T>
TicTacToe5x5<T>::TicTacToe5x5()
{
    v = vector<vector<char>>(7, vector<char>(7, start));
}

template <typename T>
bool TicTacToe5x5<T>::update_board(int x, int y, T symbol)
{
    if (!(x < 0 || x > 5 || y < 0 || y > 5) && (this->v[x][y] == '~' || symbol == '~'))
    {
        if (symbol == '~')
        {
            this->n_moves--;
            this->v[x][y] = toupper(symbol);
        }
        else
        {
            this->n_moves++;
            this->v[x][y] = toupper(symbol);
        }

        return true;
    }
    return false;
}

template <typename T>
void TicTacToe5x5<T>::display_board()
{
    int score_X = score(v, 'X');
    int score_O = score(v, 'O');

    cout << "The game state is :\n";
    cout << "    ";
    for (int i = 1; i <= 5; i++)
    {
        cout << i << "   ";
    }
    cout << "\n";
    cout << YELLOW << "  ---------------------" << RESET << "\n";
    for (int i = 1; i <= 5; i++)
    {
        cout << i << " |";

        for (int j = 1; j <= 5; j++)
        {
            if (v[i][j] == 'X')
            {
                cout << RED << " " << v[i][j] << " " << RESET << "|";
            }
            else if (v[i][j] == 'O')
            {
                cout << GREEN << " " << v[i][j] << " " << RESET << "|";
            }
            else
            {
                cout << CYAN << " " << v[i][j] << " " << RESET << "|";
            }
        }
        cout << "\n";
        cout << YELLOW << "  ---------------------" << RESET << "\n";
    }

    cout << "\n"
         << YELLOW << "=============" << RESET << "\n";
    cout << "Current Score:\n";
    cout << "Player X: " << RED << score_X << RESET << "\n";
    cout << "Player O: " << GREEN << score_O << RESET << "\n";
    cout << YELLOW << "=============" << RESET << "\n";
}

template <typename T>
bool TicTacToe5x5<T>::is_win()
{
    if (n_moves < 24)
    {
        return false;
    }
    int scoreX = score(v, 'X');
    int scoreO = score(v, 'O');
    if (scoreX > scoreO)
    {
        cout << "Player X wins with score: " << scoreX << endl;
        return true;
    }
    else if (scoreO > scoreX)
    {
        cout << "Player O wins with score: " << scoreO << endl;
        return true;
    }
    else
    {
        cout << "It's a draw, both players have equal scores." << endl;
        return false;
    }
}

template <typename T>
bool TicTacToe5x5<T>::is_draw()
{
    return (n_moves == 24 && !is_win());
}

template <typename T>
bool TicTacToe5x5<T>::game_is_over()
{
    return is_win() || is_draw();
}

template <typename T>
int TicTacToe5x5<T>::score(const vector<vector<char>> &v, const char x)
{
    int ans = 0;
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= 5; j++)
        {
            if (v[i][j] != x)
                continue;

            ans += (x == v[i + 1][j]) && (x == v[i - 1][j]);
            ans += (x == v[i][j + 1]) && (x == v[i][j - 1]);

            ans += (x == v[i - 1][j - 1]) && (x == v[i + 1][j + 1]);
            ans += (x == v[i + 1][j - 1]) && (x == v[i - 1][j + 1]);
        }
    }

    return ans;
}

template <typename T>
tic_tac_Player<T>::tic_tac_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void tic_tac_Player<T>::getmove(int &x, int &y)
{
    bool validMove = false;
    while (!validMove)
    {
        cout << "\nPlayer " << this->name << "'s turn (" << this->symbol << "), where to play? Enter row and column:\n";
        if (!(cin >> x >> y))
        {
            cout << "Invalid input! Please enter numeric values for row and column.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (x < 1 || x > 5 || y < 1 || y > 5)
        {
            cout << "Invalid input! Row and column must be between 1 and 5.\n";
        }
        else
        {
            validMove = true;
        }
    }
}

template <typename T>
tic_tac_Random_Player<T>::tic_tac_Random_Player(string Name, T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 5;
    this->name = Name;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void tic_tac_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension + 1;
    y = rand() % this->dimension + 1;
}
//==========================
void playTicTacToe5x5()
{
    int choice, ch;
    Player<char> *players[2];
    TicTacToe5x5<char> *B = new TicTacToe5x5<char>();
    string playerXName, player2Name;

    cout << BOLD << GREEN << "  Welcome to FCAI Tic_Tac_Toe Game 5x5" << RESET << endl;
    SEPARATE
    cout << BOLD << "Enter first player name [X]: " << RESET;
    getline(cin >> ws, playerXName);
    cout << BOLD << BLUE << "Choose first player type [X]:\n"
         << RESET;
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. AI Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new tic_tac_Player<char>(playerXName, 'X');
        break;
    case 2:
        players[0] = new tic_tac_Random_Player<char>(playerXName, 'X');
        break;
    case 3:
        players[0] = new X_O_MinMax5x5_Player<char>(playerXName, 'X');
        players[0]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player X. Exiting.\n";
        return;
    }

    cout << BOLD << "Enter second player name [O]: " << RESET;
    getline(cin >> ws, player2Name);
    cout << BOLD << BLUE << "Choose second player type [O]:\n"
         << RESET;
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. AI Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[1] = new tic_tac_Player<char>(player2Name, 'O');
        break;
    case 2:
        players[1] = new tic_tac_Random_Player<char>(player2Name, 'O');
        break;
    case 3:
        players[1] = new X_O_MinMax5x5_Player<char>(player2Name, 'O');
        players[1]->setBoard(B);
        break;
    default:
        cout << "Invalid choice for Player O. Exiting.\n";
        return;
    }

    // Initialize the game manager and start the game
    GameManager<char> gameManager(B, players);
    gameManager.run();

    // Clean up allocated memory
    delete B;
    delete players[0];
    delete players[1];
}

#endif // TIC_TAC_TOE_5X5_H
