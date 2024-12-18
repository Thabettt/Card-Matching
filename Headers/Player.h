//
// Created by Abdul on 11/15/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;

class Player {
private:
    string name;
    int score;

public:
    Player();
    Player(string name);
    ~Player();

    void setName(string name);
    string getName();
    void setScore(int score);
    int getScore();
    void displayScore();
};



#endif //PLAYER_H
