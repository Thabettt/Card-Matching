#ifndef BONUSCARD_H
#define BONUSCARD_H

#include "Card.h"

class BonusCard : public Card {
private:
    int bonusPoints;

public:
    BonusCard();
    BonusCard(int bonusPoints, bool visible);
    ~BonusCard();

    void display() override;
    void setBonusPoints(int bonusPoints);
    int getBonusPoints() const;

    char getChar() override;
};

#endif
