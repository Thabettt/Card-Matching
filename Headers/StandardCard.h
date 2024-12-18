#ifndef STANDARDCARD_H
#define STANDARDCARD_H

#include "Card.h"

class StandardCard : public Card {
private:
    int points;

public:
    StandardCard();
    StandardCard(int points, bool visible);
    ~StandardCard();

    void display() override;
    void setPoints(int points);
    int getPoints() const;

    char getChar() override;
};

#endif
