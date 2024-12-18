#ifndef PENALTYCARD_H
#define PENALTYCARD_H
#include "Card.h"

class PenaltyCard : public Card {
private:
     int penaltyPoints;

public:
     PenaltyCard();
     PenaltyCard(int penaltyPoints, bool visible);
     ~PenaltyCard();

     void display() override;
     void setPenaltyPoints(int penaltyPoints);
     int getPenaltyPoints();

     char getChar() override;
};

#endif
