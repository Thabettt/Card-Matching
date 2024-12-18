#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "StandardCard.h"
#include "BonusCard.h"
#include "PenaltyCard.h"

class Deck {
private:
    Card** cards;
    int totalCards;
    int gridRows;
    int gridCols;

public:
    Deck(int rows, int cols);
    ~Deck();

    void shuffle();
    void displayGrid() const;
    Card* getCard(int row, int col) const;
    void setCard(int row, int col, Card* card);

    int getTotalCards() const;
    void setTotalCards(int totalCards);

    int getGridRows() const;
    int getGridCols() const;
};

#endif