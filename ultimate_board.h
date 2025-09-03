#ifndef ULTIMATE_BOARD_H
#define ULTIMATE_BOARD_H

#include "BoardGame_Classes.h"
#include "3x3X_O.h"
#include "Validation.h"
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <set>
#include <algorithm>
#include <tuple>
#include <limits>
#include <map>
using namespace std;

template <typename T>
class ultimate_board : public Board<T> {
protected:
    X_O_Board<T> boards[10];
public:
    ultimate_board();
    bool is_win();
    T check_Winner(int x, int y);
    bool is_draw();
    void display_board();
    bool update_board(int x, int y, T mark);
    bool game_is_over();
};

template <typename T>
class ultimate_player : public Player<char> {
public:
    ultimate_player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class ultimate_Rplayer : public X_O_Random_Player<char> {
public:
    ultimate_Rplayer(string Name,T symbol);
    void getmove(int& x, int& y);
};

///=====================================Implementation

template <typename T>
ultimate_board<T>::ultimate_board() {
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool ultimate_board<T>::is_win() {
    return boards[9].is_win();
}

template <typename T>
T ultimate_board<T>::check_Winner(int x, int y) {
    for (int i = x; i < x + 3; i++) {
        if (this->board[i][y] == this->board[i][y + 1] &&
            this->board[i][y + 1] == this->board[i][y + 2] &&
            this->board[i][y] != ' ') {
            return this->board[i][y];
        }
    }
    for (int j = y; j < y + 3; j++) {
        if (this->board[x][j] == this->board[x + 1][j] &&
            this->board[x + 1][j] == this->board[x + 2][j] &&
            this->board[x][j] != ' ') {
            return this->board[x][j];
        }
    }
    if (this->board[x][y] == this->board[x + 1][y + 1] && this->board[x + 1][y + 1] == this->board[x + 2][y + 2] && this->board[x][y] != ' ') {
        return this->board[x][x];
    }
    if (this->board[x][y + 2] == this->board[x + 1][y + 1] && this->board[x + 1][y + 1] == this->board[x + 2][y] && this->board[x][y + 2] != ' ') {
        return this->board[x][x + 2];
    }
    return ' ';
}

template <typename T>
bool ultimate_board<T>::is_draw() {
    for (int i = 0; i < 9; i++) {
        if (!boards[i].is_win() && !boards[i].is_draw()) {
            return false; 
        }
    }
    return !is_win();
}


template <typename T>
void ultimate_board<T>::display_board() {
    cout << "    ";
    for (int j = 0; j < this->columns; j++) {
        cout << (j + 1) << "  ";
        if (j % 3 == 2) cout << " ";
    }
    cout << "\n   " << RED << string(30, '=') << RESET << "\n";

    for (int i = 0; i < this->rows; i++) {
        cout << (i + 1) << BLUE<< " |"<<RESET;
        for (int j = 0; j < this->columns; j++) {
            int sub_board_index = (i / 3) * 3 + (j / 3);
            if (boards[sub_board_index].is_win()) {
                char winner = check_Winner(i - i % 3, j - j % 3);
                boards[9].update_board(sub_board_index / 3, sub_board_index % 3, winner);
                for (int x = 0; x < 3; x++) {
                    for (int y = 0; y < 3; y++) {
                        this->board[i - i % 3 + x][j - j % 3 + y] = winner;
                    }
                }
            }
            char cell = this->board[i][j] == ' ' ? '.' : this->board[i][j];
            cout << " " << cell << " ";
            if (j % 3 == 2) cout << BLUE << "|" << RESET;
        }
        if (i % 3 == 2) {
            cout << "\n   " << RED << string(30, '=') << RESET << "\n";
        } else {
            cout << "\n   " << YELLOW << string(30, '-') << RESET << "\n";
        }
    }
    boards[9].display_board();
    cout << endl;
}

template <typename T>
bool ultimate_board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == ' ' || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            int sub_board_index = (x / 3) * 3 + (y / 3);
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            this->boards[sub_board_index].update_board(x % 3, y % 3, mark);
        }
        return true;
    }
    return false;
}

template <typename T>
bool ultimate_board<T>::game_is_over() {
    if (is_win()) {
        return true;
    }
    if (is_draw()) {
        cout << "The game is a draw!" << endl;        return true;
    }
    return false;
}


template <typename T>
ultimate_player<T>::ultimate_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void ultimate_player<T>::getmove(int& x, int& y) {
   bool validMove = false;
    while (!validMove) {
         cout << "\nPlayer " << this->name << "'s turn (" << this->symbol << "), where to play? Enter row and column:\n";
        if (!(cin >> x >> y)) {
            cout << "Invalid input! Please enter numeric values for row and column.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        } else if (x < 1 || x > 9 || y < 1 || y > 9) {
            cout << "Invalid input! Row and column must be between 1 and 5.\n";
        } else {
            x--; 
            y--;
            validMove = true;
        }
    }
}

template <typename T>
ultimate_Rplayer<T>::ultimate_Rplayer(string Name,T symbol) : X_O_Random_Player<T>(symbol) {
    this->dimension = 9;
    this->name = Name;
    srand(static_cast<unsigned int>(time(0))); 
}

template <typename T>
void ultimate_Rplayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}
///=====================================
void playUltimate(){
    int choice, ch;
    Player<char>* players[2];
    ultimate_board<char>* U = new ultimate_board<char>();
    string playerXName, player2Name;

     cout << BOLD << YELLOW << "Welcome to FCAI ULTIMATE X_O Game" << RESET << endl;
    SEPARATE
    cout << BOLD << "Enter first player name [X]: " << RESET;
    getline(cin >> ws, playerXName);
    cout << BOLD << BLUE << "Choose first player type [X]:\n" << RESET;
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. AI Computer\n";
    cin >> choice;

    switch (choice) {
    case 1:
        players[0] = new ultimate_player<char>(playerXName, 'X');
        break;
    case 2:
        players[0] = new ultimate_Rplayer<char>(playerXName,'X');
        break;
    default:
        cout << "Invalid choice for Player X. Exiting.\n";
        return;
    }

     cout << BOLD << "Enter second player name [O]: " << RESET;
    getline(cin >> ws, player2Name);
    cout << BOLD << BLUE << "Choose second player type [O]:\n" << RESET;
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. AI Computer\n";
    cin >> choice;

    switch (choice) {
    case 1:
        players[1] = new ultimate_player<char>(player2Name, 'O');
        break;
    case 2:
        players[1] = new ultimate_Rplayer<char>(player2Name,'O');
        break;
    default:
        cout << "Invalid choice for Player O. Exiting.\n";
        return;
    }

    GameManager<char> gameManager(U, players);
    gameManager.run();

    delete U;
    delete players[0];
    delete players[1];

}
#endif