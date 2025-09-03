#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include "BoardGame_Classes.h"
#include <fstream>
#include <string>
#include <set>
#include <cctype>
#include "AI_game4.h"
using namespace std;
class correct_indexies
{
protected:
    static vector<pair<int, int>> *correct_indexs;

public:
    // costructor to initialize the indexes
    correct_indexies()
    {
        if (!correct_indexs)
        {
            correct_indexs = new vector<pair<int, int>>{{{1, 1}, {1, 2}, {1, 3}, {2, 1}, {2, 2}, {2, 3}, {3, 1}, {3, 2}, {3, 3}}};
        }
    }
    // destructor to delete the pointers
    ~correct_indexies()
    {
        if (correct_indexs)
        {
            delete correct_indexs;
            correct_indexs = nullptr;
        }
    }
};
vector<pair<int, int>> *correct_indexies::correct_indexs = nullptr;
class words
{
protected:
    static set<string> *all_words;

public:
    words()
    {
        if (!all_words)
        {
            ifstream my_file("dic.txt");
            string line;
            this->all_words = new set<string>;
            if (my_file.is_open())
            {
                while (getline(my_file, line))
                {
                    this->all_words->insert(line);
                }
                my_file.close();
            }
        }
    }
    ~words()
    {
        if (all_words)
        {
            delete all_words;
            all_words = nullptr;
        }
    }
};
set<string> *words::all_words = nullptr;
class Word_XO_Board : public Board<char>, public correct_indexies, public words
{
protected:
public:
    // constructor to set the board size
    Word_XO_Board()
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
    // function that updates the game
    // return true if updated successfully
    // return false for wrong indexes
    bool update_board(int x, int y, char symbol) override
    {
        if (symbol == '#')
        {
            pair<int, int> a = {x, y};
            this->correct_indexs->push_back(a);
            n_moves--;
        }
        auto it = find(correct_indexies::correct_indexs->begin(), correct_indexies::correct_indexs->end(), make_pair(x, y));
        if (it == correct_indexies::correct_indexs->end())
        {
            return false;
        }
        if (symbol != '#')
        {
            this->correct_indexies::correct_indexs->erase(it);
            this->n_moves++;
        }
        this->board[x - 1][y - 1] = symbol;
        return true;
    }
    // print the game board
    void display_board() override
    {
        system("cls");
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
    }
    // return true if any player wins
    bool is_win() override
    {
        string word = "";
        for (int i = 0; i < 3; i++)
        {
            if (this->board[i][0] != '#' && this->board[i][1] != '#' && this->board[i][2] != '#')
            {
                word += this->board[i][0];
                word += this->board[i][1];
                word += this->board[i][2];
                if (this->all_words->find(word) != all_words->end())
                {
                    return true;
                }
                reverse(word.begin(), word.end());
                if (this->all_words->find(word) != all_words->end())
                {
                    return true;
                }
                word = "";
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (this->board[0][i] != '#' && this->board[1][i] != '#' && this->board[2][i] != '#')
            {
                word += this->board[0][i];
                word += this->board[1][i];
                word += this->board[2][i];
                if (this->all_words->find(word) != all_words->end())
                {
                    return true;
                }
                reverse(word.begin(), word.end());
                if (this->all_words->find(word) != all_words->end())
                {
                    return true;
                }
                word = "";
            }
        }
        if (this->board[0][0] != '#' && this->board[1][1] != '#' && this->board[2][2] != '#')
        {
            word += this->board[0][0];
            word += this->board[1][1];
            word += this->board[2][2];
            if (this->all_words->find(word) != all_words->end())
            {
                return true;
            }
            reverse(word.begin(), word.end());
            if (this->all_words->find(word) != all_words->end())
            {
                return true;
            }
            word = "";
        }
        if (this->board[0][2] != '#' && this->board[1][1] != '#' && this->board[2][0] != '#')
        {
            word += this->board[0][2];
            word += this->board[1][1];
            word += this->board[2][0];
            if (this->all_words->find(word) != all_words->end())
            {
                return true;
            }
            reverse(word.begin(), word.end());
            if (this->all_words->find(word) != all_words->end())
            {
                return true;
            }
            word = "";
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
class Word_XO_player : public Player<char>, public correct_indexies
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
    Word_XO_player(string name, char symbol) : Player<char>(name, symbol) {}
    // constructor for computer
    Word_XO_player(char symbol) : Player<char>(symbol) {}
    void getmove(int &x, int &y) override
    {
        cout << "please enter the index of your move: ";
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
        do
        {
            cout << "please enter the character of your move: ";
            cin >> this->symbol;
        } while (!isalpha(symbol));
        this->symbol = toupper(symbol);
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
class Word_XO_Random_player : public RandomPlayer<char>, public correct_indexies
{
public:
    Word_XO_Random_player(char chr) : RandomPlayer<char>(chr)
    {
        srand(static_cast<unsigned int>(time(0)));
        this->name = "Artificial stupidity ";
    }
    void getmove(int &x, int &y)
    {
        int random_index = rand() % this->correct_indexies::correct_indexs->size();
        this->symbol = char(rand() % 26 + 65);
        x = correct_indexies::correct_indexs->at(random_index).first;
        y = correct_indexies::correct_indexs->at(random_index).second;
    }
};
class Word_XO
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
        // take player info
        take_players_info(playerXName, choiceX, playerOName, choiceO);
        Word_XO_Board *B = new Word_XO_Board();
        // Set up player 1
        switch (choiceX)
        {
        case 1:
            players[0] = new Word_XO_player(playerXName, 'X');
            break;
        case 2:
            players[0] = new Word_XO_Random_player('X');
            break;
        case 3:
            players[0] = new AI_game4_Player('X');
            players[0]->setBoard(B);
            break;
        }

        // Set up player 2
        switch (choiceO)
        {
        case 1:
            players[1] = new Word_XO_player(playerOName, 'O');
            break;
        case 2:
            players[1] = new Word_XO_Random_player('O');
            break;
        case 3:
            players[1] = new AI_game4_Player('O');
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