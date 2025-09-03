#ifndef _MISERE_TIC_TAC_TOE_H
#define _MISERE_TIC_TAC_TOE_H

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
#define SEPARATE cout << RED << setw(50) << setfill('-') << "" << RESET << endl;

#include "BoardGame_Classes.h"
#include "minmax.h"
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
class MisereTicTacToeBoard : public Board<T> {
public:
    MisereTicTacToeBoard();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    void playMisereTicTacToe();
private:
    vector<vector<char>> v;
    char start = '~';
    int n_moves = 0;
    int score(const vector<vector<char>>& v, const char x);
};

template <typename T>
class MisereTicTacToePlayer : public Player<T> {
public:
    MisereTicTacToePlayer(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class MisereTicTacToeRandomPlayer : public RandomPlayer<T> {
public:
    MisereTicTacToeRandomPlayer(string Name,T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

template <typename T>
MisereTicTacToeBoard<T>::MisereTicTacToeBoard() {
    v = vector<vector<char>>(5, vector<char>(5, start));
}

template <typename T>
bool MisereTicTacToeBoard<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x > 3 || y < 0 || y > 3) && (this->v[x][y] == '~'|| mark == '~')) {
        if (mark == '~'){
            this->n_moves--;
            this->v[x][y] = toupper(mark);
        }
        else {
            this->n_moves++;
            this->v[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

template <typename T>
void MisereTicTacToeBoard<T>::display_board() {
   cout << "The game state is :\n";
    cout << "    ";  
    for (int i = 1; i <= 3; i++) {
        cout << i << "   ";  
    }
    cout << "\n";
    cout <<YELLOW << "  -------------" << RESET << "\n";  
    for (int i = 1; i <= 3; i++) {
        cout << i << " |";  

        for (int j = 1; j <= 3; j++) {
            if (v[i][j] == 'X') {
                cout << RED << " " << v[i][j] << " " << RESET << "|";  
            }
            else if (v[i][j] == 'O') {
                cout << GREEN << " " << v[i][j] << " " << RESET << "|";  
            }
            else {
                cout << CYAN << " " << v[i][j] << " " << RESET << "|";  
            }
        }
        cout << "\n";
        cout <<YELLOW << "  -------------" << RESET << "\n";  
    }
}

template <typename T>
bool MisereTicTacToeBoard<T>::is_win() {
                                        
    int scoreX = score(v, 'X');
    int scoreO = score(v, 'O');
  
    if ( scoreX == 1) {                                      
        // cout <<RED << "Player X lose "  <<RESET << endl;
        return true;
    }
    else if (scoreO == 1) {
        // cout <<RED << "Player O lose "  <<RESET<< endl;
        return true;
    }
    return false;
}

template <typename T>
bool MisereTicTacToeBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

// Check if the game is over
template <typename T>
bool MisereTicTacToeBoard<T>::game_is_over() {
    return is_win() || is_draw();
}                                                     

template <typename T>
int  MisereTicTacToeBoard<T>::score(const vector<vector<char>>& v, const char x) {
    int ans = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (v[i][j] != x) continue;
            ans += (x == v[i + 1][j]) && (x == v[i - 1][j]);
            ans += (x == v[i][j + 1]) && (x == v[i][j - 1]);
            ans += (x == v[i - 1][j - 1]) && (x == v[i + 1][j + 1]);
            ans += (x == v[i + 1][j - 1]) && (x == v[i - 1][j + 1]);
        }
    }
    return ans;
}

//--------------------------------------

template <typename T>
MisereTicTacToePlayer<T>::MisereTicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void MisereTicTacToePlayer<T>::getmove(int& x, int& y) {
   bool validMove = false;
    while (!validMove) {
        cout << "\nPlayer "  << "turn (" << this->symbol << "), where to play? Enter row and column:\n";
        if (!(cin >> x >> y)) {
            cout << "Invalid input! Please enter numeric values for row and column.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        } else if (x < 1 || x > 3 || y < 1 || y > 3) {
            cout << "Invalid input! Row and column must be between 1 and 5.\n";
        } else {
            validMove = true;
        }
    }
}
                                                                       
template <typename T>
MisereTicTacToeRandomPlayer<T>::MisereTicTacToeRandomPlayer(string Name,T symbol) : RandomPlayer<T>( symbol) {
    this->dimension = 3;
    this->name = Name;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void MisereTicTacToeRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension + 1; 
    y = rand() % this->dimension + 1;
}
//=====================================
void playMisereTicTacToe()
{
     int choice, ch;
    Player<char>* players[2];
    MisereTicTacToeBoard<char>* C = new MisereTicTacToeBoard<char>();
    string playerXName, player2Name;

        cout << BOLD << GREEN << "Welcome to FCAI Misere Tic_Tac_Toe Game " << RESET << endl;
        SEPARATE

        cout << BOLD << "Enter first player name [X]: " << RESET;
        getline(cin>>ws, playerXName) ;
        cout << BOLD << "Enter second player name [O]: " << RESET;
        getline(cin>>ws, player2Name);
        cout << BOLD << BLUE << "Choose first player type [X]:\n" << RESET;
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "3. Smart Computer (AI)\n";
        cin >> choice;

        switch (choice) {
        case 1:
            players[0] = new MisereTicTacToePlayer<char>(player2Name, 'X');  // Human Player X
            break;
        case 2:
            players[0] = new MisereTicTacToeRandomPlayer<char>(player2Name,'X');  // Random Computer Player X
            break;
        case 3:
            players[0] = new X_O_MinMax_Player<char>(player2Name,'X');
            players[0]->setBoard(C);
            break;
        
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
        }

        cout << BOLD << BLUE << "Choose second player type [O]:\n" << RESET;
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "3. Smart Computer (AI)\n";
        cin >> choice;

        switch (choice) {
        case 1:
            players[1] = new MisereTicTacToePlayer<char>(playerXName, 'O');  // Human Player O
            break;
        case 2:
            players[1] = new MisereTicTacToeRandomPlayer<char>(playerXName,'O');  // Random Computer Player O
            break;
        case 3:
            players[1] = new X_O_MinMax_Player<char>(playerXName,'O');
            players[1]->setBoard(C);
            break;
       
        default:
          {  cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;}
        }

    GameManager<char> MiserTicTacToe(C, players);
    MiserTicTacToe.run();

    delete C;
    delete players[0];
    delete players[1];
}

#endif //_MISERE_TIC_TAC_TOE_H
