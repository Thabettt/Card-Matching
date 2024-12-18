#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
using namespace std;

class Card {
private:
    bool visible;

public:
    Card();
    virtual ~Card();
    Card(bool visible);

    virtual void display();
    virtual char getChar();

    void setVisible(bool visible);
    bool isVisible() const;
};

#endif
