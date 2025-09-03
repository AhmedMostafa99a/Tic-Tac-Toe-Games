#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <set>
#include <utility>
#include <algorithm>
#include <tuple>
#include <limits>
#include <map>
#include <cmath>
#include "BoardGame_Classes.h"
#include "AI_game1.h"
// #include "bits/stdc++.h"
using namespace std;
class correct_indecies
{
protected:
    static vector<pair<int, int>> *correct_index;

public:
    // costructor to initialize the indexes
    correct_indecies()
    {
        if (!correct_index)
        {
            correct_index = new vector<pair<int, int>>{{{1, 3}, {2, 2}, {2, 3}, {2, 4}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}}};
        }
    }
    // destructor to delete the pointers
    ~correct_indecies()
    {
        if (correct_index)
        {
            delete correct_index;
            correct_index = nullptr;
        }
    }
};
vector<pair<int, int>> *correct_indecies::correct_index = nullptr;
class Triangle_XO_Board : public Board<char>, public correct_indecies
{
private:
    vector<pair<int, int>> index;

public:
    // constructor to set the board size
    Triangle_XO_Board()
    {
        this->rows = 3;
        this->columns = 5;
        this->board = new char *[this->rows];
        for (int i = 0; i < this->rows; i++)
        {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++)
            {
                this->board[i][j] = '#';
            }
        }
        this->n_moves = 0;
        index.resize(9);
        index = {{{1, 3}, {2, 2}, {2, 3}, {2, 4}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}}};
    }
    // function that updates the game
    // return true if updated successfully
    // return false for wrong indexes
    bool update_board(int x, int y, char symbol)
    {
        if (symbol == '#')
        {
            n_moves--;
            pair<int, int> a = {x, y};
            this->correct_index->push_back(a);
        }
        auto it = find(correct_indecies::correct_index->begin(), correct_indecies::correct_index->end(), make_pair(x, y));
        if (it == correct_indecies::correct_index->end())
        {
            return false;
        }
        if (symbol != '#')
        {
            this->correct_indecies::correct_index->erase(it);
            this->n_moves++;
        }
        this->board[x - 1][y - 1] = symbol;
        return true;
    }
    // print the game board
    void display_board() override
    {
        system("cls");
        cout << "  1 2 3 4 5\n";
        cout << "1     " << this->board[0][2] << '\n';
        cout << "2   " << this->board[1][1] << " " << this->board[1][2] << " " << this->board[1][3] << '\n';
        cout << "3 " << this->board[2][0] << " " << this->board[2][1] << " " << this->board[2][2] << " " << this->board[2][3] << " " << this->board[2][4] << '\n';
    }
    // return true if any player wins
    bool is_win() override
    {
        if ((this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] && this->board[0][2] != '#') ||
            (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != '#') ||
            (this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != '#') ||
            (this->board[1][1] == this->board[1][2] && this->board[1][1] == this->board[1][3] && this->board[1][1] != '#') ||
            (this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2] && this->board[2][0] != '#') ||
            (this->board[2][1] == this->board[2][2] && this->board[2][2] == this->board[2][3] && this->board[2][1] != '#') ||
            (this->board[2][2] == this->board[2][3] && this->board[2][3] == this->board[2][4] && this->board[2][2] != '#'))
        {
            return true;
        }
        return false;
    }
    // return true if the game ended and no one have one yet
    bool is_draw() override
    {
        return (!is_win() && this->n_moves == 9);
    }
    // return true when the game ends
    bool game_is_over() override
    {
        return is_win() || is_draw();
    }
};
class Triangle_XO_player : public Player<char>, public correct_indecies
{
private:
    string name;
    char symbol;
    // makes sure that input is a number
    float ReadNumber(string message = "")
    {
        float number;
        cout << message;
        cin >> number;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Number, Enter a valid one" << endl;
            cin >> number;
        }
        return number;
    }

public:
    // constructor for human palyer
    Triangle_XO_player(string name, char symbol) : Player<char>(name, symbol) {}
    // constructor for computer
    Triangle_XO_player(char symbol) : Player<char>(symbol) {}
    void getmove(int &x, int &y) override
    {
        cout << "please enter the index of your move\n";
        x = ReadNumber();
        y = ReadNumber();
        auto it = find(correct_indecies::correct_index->begin(), correct_indecies::correct_index->end(), make_pair(x, y));
        while (it == correct_indecies::correct_index->end())
        {
            cout << "you entered a wrong index please enter a correct index\n";
            cout << "please enter the index of your move\n";
            x = ReadNumber();
            y = ReadNumber();
            it = find(correct_indecies::correct_index->begin(), correct_indecies::correct_index->end(), make_pair(x, y));
        }
    }
    string getName()
    {
        return name;
    }
    char getSymbol()
    {
        return symbol;
    }
};
class Triangle_XO_Random_player : public RandomPlayer<char>, public correct_indecies
{
public:
    Triangle_XO_Random_player(char chr) : RandomPlayer<char>(chr)
    {
        srand(static_cast<unsigned int>(time(0)));
        this->name = "Artificial stupidity ";
    }
    void getmove(int &x, int &y)
    {
        int random_index = rand() % this->correct_indecies::correct_index->size();
        x = correct_indecies::correct_index->at(random_index).first;
        y = correct_indecies::correct_index->at(random_index).second;
    }
};
class Triangle_XO
{
private:
    // A function that reads string with spaces
    string readString(string const &message)
    {
        cout << message;
        string sentence;
        getline(cin >> ws, sentence);
        return sentence;
    }
    // makes sure that input is a number
    float ReadNumber(string const &message)
    {
        float number;
        cout << message;
        cin >> number;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Number, Enter a valid one" << endl;
            cin >> number;
        }
        return number;
    }
    // makes input is a number and in a certain range
    int readNumInRange(string message, int from, int to)
    {
        int num;
        do
        {
            num = ReadNumber(message);
        } while (round(num) != num || num > to || num < from);
        return num;
    }
    // takes players name and kind
    void take_players_info(string &Xname, int &Xkind, string &Oname, int &Okind)
    {
        Xname = readString("please Enter Player X name: ");
        cout << "1) Human\n";
        cout << "2) Random Computer\n";
        cout << "3) Smart Computer (AI)\n";
        Xkind = readNumInRange("Choose Player X type : ", 1, 3);

        Oname = readString("please Enter Player O name: ");
        cout << "1) Human\n";
        cout << "2) Random Computer\n";
        cout << "3) Smart Computer (AI)\n";
        Okind = readNumInRange("Choose Player O type : ", 1, 3);
    }

public:
    // start the game function
    void start_Triangle_XO()
    {
        Player<char> *players[2];
        string playerXName, playerOName;
        int choiceX, choiceO;
        Triangle_XO_Board *B = new Triangle_XO_Board();
        // take player info
        take_players_info(playerXName, choiceX, playerOName, choiceO);
        // Set up player 1
        switch (choiceX)
        {
        case 1:
            players[0] = new Triangle_XO_player(playerXName, 'X');
            break;
        case 2:
            players[0] = new Triangle_XO_Random_player('X');
            break;
        case 3:
            players[0] = new AI_game1('X');
            players[0]->setBoard(B);
            break;
        }

        // Set up player 2
        switch (choiceO)
        {
        case 1:
            players[1] = new Triangle_XO_player(playerOName, 'O');
            break;
        case 2:
            players[1] = new Triangle_XO_Random_player('O');
            break;
        case 3:
            players[1] = new AI_game1('O');
            players[1]->setBoard(B);
            break;
        }

        GameManager<char> triangle_XO(B, players);
        triangle_XO.run();

        delete B;
        for (int i = 0; i < 2; ++i)
        {
            delete players[i];
        }
    }
};
