#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Player.h"

class Game {
private:
    Deck* deck;
    Player* player1;
    Player* player2;
    int currentPlayer;

public:
    Game();
    ~Game();

    void initializeGame(Player* player1, Player* player2);
    void startGame();
    void displayGrid() const;
    void switchPlayer();
    void endGame();
    int getCurrentPlayer() const;
    void printGrid() const;
    bool isValidMove(int row1, int col1, int row2, int col2) const;
    void flipAndRevealCards(int row1, int col1, int row2, int col2);
    bool checkGameOver() const;
    void printGridAllVisibleOnce();
};

#endif