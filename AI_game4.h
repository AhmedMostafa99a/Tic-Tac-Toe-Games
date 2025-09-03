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
class AI_game4_Player : public Player<char> {
public:
    AI_game4_Player(char symbol);
    void getmove(int& x, int& y) override;

private:
    pair<int, int> getBest_nextMove();
};

// Constructor for the templated class
AI_game4_Player::AI_game4_Player(char symbol) : Player<char>(symbol) {
    this->name = "AI Player";
    srand(static_cast<unsigned int>(time(0)));
}

// Method to get the best move for the player
void AI_game4_Player::getmove(int& x, int& y) {
    pair<int, int> bestMove = getBest_nextMove();
    x = bestMove.first;
    y = bestMove.second;
}
// Find the best move using the minimax algorithm
pair<int, int> AI_game4_Player::getBest_nextMove() {
    // First, check if we can win in the next move
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            for ( int k = 0; k < 26; k++)
            {
                if (this->boardPtr->update_board(i, j, char('A' + k))) {
                    if (this->boardPtr->is_win()) {
                        this->boardPtr->update_board(i, j, '#'); // Undo move
                        this->symbol = char('A' + k);
                        return { i, j }; // Winning move found
                    }
                    this->boardPtr->update_board(i, j, '#'); // Undo move
                }
            }
        }
    }
    int x = rand() % 3 + 1;
    int y = rand() % 3 + 1;
    int k = rand() % 26;
    this->symbol = char('A' + k);
    return { x,y };
}