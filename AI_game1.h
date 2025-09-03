#pragma once
#pragma once
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <set>
#include <utility>
#include <algorithm>
#include <tuple>
#include <limits>
#include <map>

#include "BoardGame_Classes.h"
using namespace std;
class AI_game1 : public Player<char> {
private:
    vector<pair<int, int>>correct_positions;
    pair<int, int> getBest_Move();
    int calculate_min_max(char symbol, bool playerTurn);
public:
    AI_game1(char symbol);
    void getmove(int& x, int& y) override;
     
};
// Constructor for the class
AI_game1::AI_game1(char symbol) : Player<char>(symbol) {
    this->name = "AI Player";
    correct_positions.resize(9);
                        correct_positions={ { { 1, 3 }
                                  , { 2, 2 }, { 2, 3 }, { 2, 4 }
                        , { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 } } };
    srand(static_cast<unsigned int>(time(0)));
}
// Method to get the best move for the player
void AI_game1::getmove(int& x, int& y) {
    pair<int, int> bestMove = getBest_Move();
    x = bestMove.first;
    y = bestMove.second;
}
int AI_game1::calculate_min_max(char symbol, bool playerTurn) {
    //base case
    if (this->boardPtr->is_win()) {
        return playerTurn ? -1 : 1;
    }
    else if (this->boardPtr->is_draw()) {
        return 0;
    }
    int who_is_winning = playerTurn ? -1 : 1;
    char opponentSymbol = (symbol == 'X') ? 'O' : 'X';
    for (int j = 0; j < 9; ++j) {
        if (this->boardPtr->update_board(correct_positions[j].first, correct_positions[j].second, opponentSymbol)) {
            int value = calculate_min_max(opponentSymbol, !playerTurn);
            this->boardPtr->update_board(correct_positions[j].first, correct_positions[j].second, '#'); // Undo move
            if (playerTurn) {
                who_is_winning = std::max(who_is_winning, value);
            }
            else {
                who_is_winning = std::min(who_is_winning, value);
            }
        }
    }
}
pair < int, int> AI_game1::getBest_Move() {
    int bestMove = -1;
    pair<int, int> BestMove;
    char opponent = (symbol == 'X') ? 'O' : 'X';
    //win the next move
    for (int i = 0; i < 9; ++i) {
        if (this->boardPtr->update_board(correct_positions[i].first, correct_positions[i].second, this->symbol)) {
            if (boardPtr->is_win()) {
                this->boardPtr->update_board(correct_positions[i].first, correct_positions[i].second, '#'); // Undo move
                return correct_positions[i];
            }
            this->boardPtr->update_board(correct_positions[i].first, correct_positions[i].second, '#'); // Undo move
        }
    }
    //block the opponent next win
    for (int i = 0; i < 9; ++i) {
        if (this->boardPtr->update_board(correct_positions[i].first, correct_positions[i].second, opponent)) {
            if (boardPtr->is_win()) {
                this->boardPtr->update_board(correct_positions[i].first, correct_positions[i].second, '#'); // Undo move
                return correct_positions[i];
            }
            this->boardPtr->update_board(correct_positions[i].first, correct_positions[i].second, '#'); // Undo move
        }
    }
    //check for the best move
    for (int i = 0; i <9; ++i) {
            if (this->boardPtr->update_board(correct_positions[i].first, correct_positions[i].second ,this->symbol)) {
                 int move = calculate_min_max(this->symbol, 0);
                 this->boardPtr->update_board(correct_positions[i].first, correct_positions[i].second, '#'); // Undo move
                 if (move > bestMove) {
                      BestMove = { correct_positions[i]};
                      bestMove = move;
                 }
            }
    }
    return BestMove;
}

