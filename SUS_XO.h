#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include "BoardGame_Classes.h"
#include <fstream>
#include <cmath>
#include <string>
#include <set>
#include <cctype>
#include "Word_XO.h"
using namespace std;

// Global Variables:
int moves = 0;

class SUS_XO_Board : public Board<char>, public correct_indexies
{
private:
    int Scounter = 0;
    int Ucounter = 0;

protected:
public:
    // constructor to set the board size
    SUS_XO_Board()
    {
        this->rows = 3;
        this->columns = 3;
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
    }
    // return the number of SUS's
    int num_of_SUS()
    {
        string word = "";
        int counter = 0;
        // search for column winer
        for (int i = 0; i < 3; i++)
        {
            if (this->board[i][0] != '#' && this->board[i][1] != '#' && this->board[i][2] != '#')
            {
                word += this->board[i][0];
                word += this->board[i][1];
                word += this->board[i][2];
                if (word == "SUS")
                {
                    counter++;
                }
                word = "";
            }
        }
        // search for row winer
        for (int i = 0; i < 3; i++)
        {
            if (this->board[0][i] != '#' && this->board[1][i] != '#' && this->board[2][i] != '#')
            {
                word += this->board[0][i];
                word += this->board[1][i];
                word += this->board[2][i];
                if (word == "SUS")
                {
                    counter++;
                }
                word = "";
            }
        }
        // search for principle diagonal winner
        if (this->board[0][0] != '#' && this->board[1][1] != '#' && this->board[2][2] != '#')
        {
            word += this->board[0][0];
            word += this->board[1][1];
            word += this->board[2][2];
            if (word == "SUS")
            {
                counter++;
            }
            word = "";
        }
        // search for subprinciple diagonal winner
        if (this->board[0][2] != '#' && this->board[1][1] != '#' && this->board[2][0] != '#')
        {
            word += this->board[0][2];
            word += this->board[1][1];
            word += this->board[2][0];
            if (word == "SUS")
            {
                counter++;
            }
            word = "";
        }
        return counter;
    }
    // function that updates the game
    // return true if updated successfully
    // return false for wrong indexes
    bool update_board(int x, int y, char symbol) override
    {
        if (moves != 9)
        {
            auto it = find(correct_indexies::correct_indexs->begin(), correct_indexies::correct_indexs->end(), make_pair(x, y));
            if (it == correct_indexies::correct_indexs->end())
            {
                return false;
            }
            this->correct_indexies::correct_indexs->erase(it);
            this->n_moves++;
            moves++;
            this->board[x - 1][y - 1] = symbol;
            int num_of_SUS_s = num_of_SUS();
            if (num_of_SUS_s > Scounter + Ucounter)
            {
                if (symbol == 'S')
                {
                    Scounter = (num_of_SUS_s - Ucounter);
                }
                else
                {
                    Ucounter = (num_of_SUS_s - Scounter);
                }
            }
            return true;
        }
        this->n_moves++;
        moves++;
        return true;
    }
    // print the game board
    void display_board() override
    {
        if (moves == 9 && Ucounter > Scounter)
        {
            return;
        }
        // system("cls");
        cout << "  1 2 3\n";
        for (int i = 0; i < this->rows; i++)
        {
            cout << i + 1 << " ";
            for (int j = 0; j < this->columns; j++)
            {
                cout << this->board[i][j] << ' ';
            }
            cout << '\n';
        }
        cout << "S counter: " << Scounter << '\n';
        cout << "U counter: " << Ucounter << '\n';
    }
    // return true if any player wins
    bool is_win() override
    {
        if (this->n_moves == 9 && Scounter > Ucounter)
        {
            return true;
        }
        if (this->n_moves == 10 && Ucounter > Scounter)
        {
            return true;
        }
        return false;
    }
    // return true if the game ended and no one have one yet
    bool is_draw() override
    {
        return (!is_win() && this->n_moves == 10);
    }
    // return true when the game ends
    bool game_is_over() override
    {
        return is_win() || is_draw();
    }
};
class SUS_XO_player : public Player<char>, public correct_indexies
{
private:
    string name;
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
    SUS_XO_player(string name, char symbol) : Player<char>(name, symbol) {}
    // constructor for computer
    SUS_XO_player(char symbol) : Player<char>(symbol) {}
    void getmove(int &x, int &y) override
    {
        if (moves == 9)
        {
            return;
        }
        cout << "\nPlayer " << this->name << "'s turn (" << this->symbol << "), where to play? Enter row and column:\n";
        x = ReadNumber();
        y = ReadNumber();
        auto it = find(correct_indexies::correct_indexs->begin(), correct_indexies::correct_indexs->end(), make_pair(x, y));
        while (it == correct_indexies::correct_indexs->end())
        {
            cout << "you entered a wrong index please enter a correct index\n";
            cout << "please enter the index of your move\n";
            x = ReadNumber();
            y = ReadNumber();
            it = find(correct_indexies::correct_indexs->begin(), correct_indexies::correct_indexs->end(), make_pair(x, y));
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
class SUS_XO_Random_player : public RandomPlayer<char>, public correct_indexies
{
public:
    SUS_XO_Random_player(char chr) : RandomPlayer<char>(chr)
    {
        srand(static_cast<unsigned int>(time(0)));
        this->name = "Artificial stupidity ";
    }
    void getmove(int &x, int &y)
    {
        if (moves == 9)
        {
            return;
        }
        int random_index = rand() % this->correct_indexies::correct_indexs->size();
        x = correct_indexies::correct_indexs->at(random_index).first;
        y = correct_indexies::correct_indexs->at(random_index).second;
    }
};
class SUS_XO
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
        // first Player name and type
        Xname = readString("please Enter Player S name: ");
        cout << "1) Human\n";
        cout << "2) Random Computer\n";
        cout << "3) Smart Computer (AI)\n";
        Xkind = readNumInRange("Choose Player S type : ", 1, 3);
        // Second Player name and type
        Oname = readString("please Enter Player U name: ");
        cout << "1) Human\n";
        cout << "2) Random Computer\n";
        cout << "3) Smart Computer (AI)\n";
        Okind = readNumInRange("Choose Player U type : ", 1, 3);
    }

public:
    // start the game function
    void start_SUS_XO()
    {
        Player<char> *players[2];
        string playerXName, playerOName;
        int choiceX, choiceO;
        // take player info
        take_players_info(playerXName, choiceX, playerOName, choiceO);
        // Set up player 1
        switch (choiceX)
        {
        case 1:
            players[0] = new SUS_XO_player(playerXName, 'S');
            break;
        case 2:
            players[0] = new SUS_XO_Random_player('S');
            break;
        }

        // Set up player 2
        switch (choiceO)
        {
        case 1:
            players[1] = new SUS_XO_player(playerOName, 'U');
            break;
        case 2:
            players[1] = new SUS_XO_Random_player('U');
            break;
        }
        SUS_XO_Board *B = new SUS_XO_Board();
        GameManager<char> SUS_XO(B, players);
        SUS_XO.run();

        delete B;
        for (int i = 0; i < 2; ++i)
        {
            delete players[i];
        }
    }
};
