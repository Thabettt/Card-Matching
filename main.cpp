#include <iostream>
#include "Headers/Game.h"
#include "Headers/Player.h"
#include "Headers/Deck.h"
#include "Headers/Card.h"
#include "Headers/StandardCard.h"
#include "Headers/BonusCard.h"
#include "Headers/PenaltyCard.h"
#include <ctime>
using namespace std;

//////////////////////// Card.cpp ////////////////////////
/// Card class implementation
Card::Card() {
    visible = false;
}
Card::Card(bool visible) {
    this->visible = visible;
}
Card::~Card() {
}
void Card::display() {
    if (visible) {
        cout << "Visible" << endl;
    } else {
        cout << "Not visible" << endl;
    }
}
void Card::setVisible(bool visible) {
    this->visible = visible;
}
bool Card::isVisible() const {
    return visible;
}
char Card::getChar() {
}
//////////////////////// StandardCard.cpp ////////////////////////
/// StandardCard class implementation
StandardCard::StandardCard() {
    points = 0;
}
StandardCard::StandardCard(int points, bool visible) : Card(visible) {
    this->points = points;
}
StandardCard::~StandardCard() {
}
void StandardCard::display() {
    string visibleStr = this->isVisible() ? "visible" : "not visible";
    cout << "Standard card with " << this->getPoints() << " points and it is " << visibleStr << endl;
}
void StandardCard::setPoints(int points) {
    this->points = points;
}
int StandardCard::getPoints() const {
    return points;
}
char StandardCard::getChar() {
    return this->getPoints() + '0';
}
//////////////////////// BonusCard.cpp ////////////////////////
/// BonusCard class implementation
BonusCard::BonusCard() {
    bonusPoints = 0;
}
BonusCard::BonusCard(int bonusPoints, bool visible) : Card(visible) {
    this->bonusPoints = bonusPoints;
}
BonusCard::~BonusCard() {
}
void BonusCard::display() {
    string visibleStr = this->isVisible() ? "visible" : "not visible";
    cout << "Bonus card with " << this->getBonusPoints() << " bonus points and it is " << visibleStr << endl;
}
void BonusCard::setBonusPoints(int bonusPoints) {
    this->bonusPoints = bonusPoints;
}

int BonusCard::getBonusPoints() const {
    return bonusPoints;
}
char BonusCard::getChar() {
    return '7';
}
//////////////////////// PenaltyCard.cpp ////////////////////////
/// PenaltyCard class implementation
PenaltyCard::PenaltyCard() {
    penaltyPoints = 0;
}
PenaltyCard::PenaltyCard(int penaltyPoints, bool visible) : Card(visible) {
    this->penaltyPoints = penaltyPoints;
}
PenaltyCard::~PenaltyCard() {
}
void PenaltyCard::display() {
    string visibleStr = this->isVisible() ? "visible" : "not visible";
    cout << "Penalty card with " << this->getPenaltyPoints() << " penalty points and it is " << visibleStr << endl;
}
void PenaltyCard::setPenaltyPoints(int penaltyPoints) {
    this->penaltyPoints = penaltyPoints;
}
int PenaltyCard::getPenaltyPoints() {
    return penaltyPoints;
}
char PenaltyCard::getChar() {
    return '8';
}
//////////////////////// Deck.cpp ////////////////////////
/// Deck class implementation

Deck::Deck(int rows, int cols) {
    totalCards = 0;
    gridRows = rows;
    gridCols = cols;

    cards = new Card*[gridRows * gridCols];
    for (int i = 0; i < gridRows * gridCols; ++i) {
        cards[i] = nullptr;
    }
}

Deck::~Deck() {
    for (int i = 0; i < gridRows * gridCols; ++i) {
        delete cards[i]; // Delete each Card
    }
    delete[] cards; // Delete the array of Card pointers
}

void Deck::shuffle() {
    int totalCards = gridRows * gridCols;

    srand(time(0));
    for (int i = totalCards - 1; i > 0; --i) {
        int randIndex = rand() % (i + 1);
        Card* temp = cards[i];
        cards[i] = cards[randIndex];
        cards[randIndex] = temp;
    }
}

void Deck::displayGrid() const {
    for (int i = 0; i < gridRows; ++i) {
        for (int j = 0; j < gridCols; ++j) {
            if (cards[i * gridCols + j] != nullptr) {
                cards[i * gridCols + j]->display();
            } else {
                cout << "Empty ";
            }
        }
        cout << endl;
    }
}

Card* Deck::getCard(int row, int col) const {
    return cards[row * gridCols + col];
}

void Deck::setCard(int row, int col, Card* card) {
    cards[row * gridCols + col] = card;
}

int Deck::getTotalCards() const {
    return totalCards;
}

void Deck::setTotalCards(int totalCards) {
    this->totalCards = totalCards;
}

int Deck::getGridRows() const {
    return gridRows;
}

int Deck::getGridCols() const {
    return gridCols;
}

//////////////////////// Game.cpp ////////////////////////
/// Game class implementation

Game::Game() {
    deck = nullptr;
    player1 = nullptr;
    player2 = nullptr;
    currentPlayer = 1;
}

Game::~Game() {
    delete deck;
    delete player1;
    delete player2;
}

void Game::initializeGame(Player* player1, Player* player2) {
    this->player1 = player1;
    this->player2 = player2;

    deck = new Deck(4, 4);
    int index = 0;
    for (int i = 1; i <= 6; ++i) {
        deck->setCard(index / 4, index % 4, new StandardCard(i, true));
        index++;
        deck->setCard(index / 4, index % 4, new StandardCard(i, true));
        index++;
    }

    deck->setCard(index / 4, index % 4, new BonusCard(3, true));
    index++;
    deck->setCard(index / 4, index % 4, new BonusCard(3, true));
    index++;

    deck->setCard(index / 4, index % 4, new PenaltyCard(-2, true));
    index++;
    deck->setCard(index / 4, index % 4, new PenaltyCard(-2, true));
    index++;

    deck->setTotalCards(index);

    deck->shuffle();
    printGrid();
}

void Game::startGame() {
    // Start the game logic
}

void Game::displayGrid() const {
    deck->displayGrid();
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

void Game::endGame() {
    // End the game logic
}

int Game::getCurrentPlayer() const {
    return currentPlayer;
}

void Game::printGrid() const {
    for (int i = 0; i < deck->getGridRows(); i++) {
        for (int j = 0; j < deck->getGridCols(); j++) {
            if (deck->getCard(i, j)->isVisible()) {
                cout << deck->getCard(i, j)->getChar() << "  ";
            } else {
                cout << "*  ";
            }
        }
        cout << endl;
    }
}
//////////////////////// Player.cpp ////////////////////////
/// Player class implementation
Player::Player() {
    name = "";
    score = 0;
}
Player::Player(string name) {
    this->name = name;
    score = 0;
}
Player::~Player() {
}
void Player::setName(string name) {
    this->name = name;
}
string Player::getName() {
    return name;
}
void Player::setScore(int score) {
    this->score = score;
}
int Player::getScore() {
    return score;
}
void Player::displayScore() {
    cout << "Player " << name << " has " << score << " points" << endl;
}

//////////////////////// main.cpp ////////////////////////
///

int main() {
    // Create players
    Player* player1 = new Player("Alice");
    Player* player2 = new Player("Bob");

    // Initialize game
    Game game;
    game.initializeGame(player1, player2);

    return 0;
}