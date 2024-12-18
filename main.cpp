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

void Game::printGridAllVisibleOnce() {
    // Temporarily set all cards to visible
    for (int i = 0; i < deck->getGridRows(); i++) {
        for (int j = 0; j < deck->getGridCols(); j++) {
            Card* card = deck->getCard(i, j);
            if (card != nullptr) {
                card->setVisible(true);
            }
        }
    }

    // Print the grid
    printGrid();

    // Set all cards back to their original visibility state
    for (int i = 0; i < deck->getGridRows(); i++) {
        for (int j = 0; j < deck->getGridCols(); j++) {
            Card* card = deck->getCard(i, j);
            if (card != nullptr) {
                card->setVisible(false);
            }
        }
    }
}

void Game::initializeGame(Player* player1, Player* player2) {
    this->player1 = player1;
    this->player2 = player2;

    deck = new Deck(4, 4);
    int index = 0;
    for (int i = 1; i <= 6; ++i) {
        deck->setCard(index / 4, index % 4, new StandardCard(i, false));
        index++;
        deck->setCard(index / 4, index % 4, new StandardCard(i, false));
        index++;
    }

    deck->setCard(index / 4, index % 4, new BonusCard(3, false));
    index++;
    deck->setCard(index / 4, index % 4, new BonusCard(3, false));
    index++;

    deck->setCard(index / 4, index % 4, new PenaltyCard(-2, false));
    index++;
    deck->setCard(index / 4, index % 4, new PenaltyCard(-2, false));
    index++;

    deck->setTotalCards(index);

    deck->shuffle();

    printGridAllVisibleOnce();
    printGrid();

    // Start the game
    startGame();
}

void Game::startGame() {
    bool gameOver = false;
    while (!gameOver) {
        cout << (currentPlayer == 1 ? player1->getName() : player2->getName()) << " (Player " << currentPlayer << ")'s turn. Current score: " << (currentPlayer == 1 ? player1->getScore() : player2->getScore()) << endl;
        int row1, col1, row2, col2;
        cout << "Enter the coordinates of the first card (row and column): ";
        cin >> row1 >> col1;
        cout << "Enter the coordinates of the second card (row and column): ";
        cin >> row2 >> col2;

        row1 -= 1;
        row2 -= 1;
        col1 -= 1;
        col2 -= 1;

        // Validate input
        if (!isValidMove(row1, col1, row2, col2)) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        // Flip and reveal the selected cards
        flipAndRevealCards(row1, col1, row2, col2);

        // Check if the game is over
        gameOver = checkGameOver();

        // Switch player if the game is not over
        if (!gameOver) {
            switchPlayer();
        }
    }
    endGame();
}

bool Game::isValidMove(int row1, int col1, int row2, int col2) const {
    int rows = deck->getGridRows();
    int cols = deck->getGridCols();
    return row1 >= 0 && row1 < rows && col1 >= 0 && col1 < cols &&
           row2 >= 0 && row2 < rows && col2 >= 0 && col2 < cols &&
           !(row1 == row2 && col1 == col2) &&
           deck->getCard(row1, col1) != nullptr &&
           deck->getCard(row2, col2) != nullptr;
}

void Game::flipAndRevealCards(int row1, int col1, int row2, int col2) {
    Card* card1 = deck->getCard(row1, col1);
    Card* card2 = deck->getCard(row2, col2);

    card1->setVisible(true);
    card2->setVisible(true);

    cout << endl; // Add a newline before printing the grid
    printGrid();

    StandardCard* standardCard1 = dynamic_cast<StandardCard*>(card1);
    StandardCard* standardCard2 = dynamic_cast<StandardCard*>(card2);
    BonusCard* bonusCard1 = dynamic_cast<BonusCard*>(card1);
    BonusCard* bonusCard2 = dynamic_cast<BonusCard*>(card2);
    PenaltyCard* penaltyCard1 = dynamic_cast<PenaltyCard*>(card1);
    PenaltyCard* penaltyCard2 = dynamic_cast<PenaltyCard*>(card2);

    if (standardCard1 && standardCard2 && standardCard1->getPoints() == standardCard2->getPoints()) {
        // Both cards are standard cards and they match
        cout << "Cards match! Player " << currentPlayer << " gains 1 point and takes another turn." << endl;
        if (currentPlayer == 1) {
            player1->setScore(player1->getScore() + 1);
        } else {
            player2->setScore(player2->getScore() + 1);
        }
        deck->setCard(row1, col1, nullptr);
        deck->setCard(row2, col2, nullptr);
    } else if ((penaltyCard1 && standardCard2) || (penaltyCard2 && standardCard1)) {
        // One card is a penalty card and the other is a standard card
        cout << "One penalty card revealed! Player " << currentPlayer << " loses 1 point." << endl;
        if (currentPlayer == 1) {
            player1->setScore(player1->getScore() - 1);
        } else {
            player2->setScore(player2->getScore() - 1);
        }
        if (penaltyCard1) {
            deck->setCard(row1, col1, nullptr);
            card2->setVisible(false);
        } else {
            deck->setCard(row2, col2, nullptr);
            card1->setVisible(false);
        }
    } else if (penaltyCard1 && penaltyCard2) {
        // Both cards are penalty cards
        cout << "Two penalty cards revealed! Player " << currentPlayer << " has two options:" << endl;
        cout << "1. Lose 2 points." << endl;
        cout << "2. Lose 1 point and skip the next turn." << endl;
        int choice;
        cin >> choice;
        if (choice == 1) {
            if (currentPlayer == 1) {
                player1->setScore(player1->getScore() - 2);
            } else {
                player2->setScore(player2->getScore() - 2);
            }
        } else {
            if (currentPlayer == 1) {
                player1->setScore(player1->getScore() - 1);
            } else {
                player2->setScore(player2->getScore() - 1);
            }
        }
        deck->setCard(row1, col1, nullptr);
        deck->setCard(row2, col2, nullptr);
    } else if ((bonusCard1 && standardCard2) || (bonusCard2 && standardCard1)) {
        // One card is a bonus card and the other is a standard card
        cout << "One bonus card revealed! Player " << currentPlayer << " gains 1 point." << endl;
        if (currentPlayer == 1) {
            player1->setScore(player1->getScore() + 1);
        } else {
            player2->setScore(player2->getScore() + 1);
        }
        if (bonusCard1) {
            deck->setCard(row1, col1, nullptr);
            card2->setVisible(false);
        } else {
            deck->setCard(row2, col2, nullptr);
            card1->setVisible(false);
        }
    } else if (bonusCard1 && bonusCard2) {
        // Both cards are bonus cards
        cout << "Two bonus cards revealed! Player " << currentPlayer << " has two options:" << endl;
        cout << "1. Gain 2 points." << endl;
        cout << "2. Gain 1 point and take another turn." << endl;
        int choice;
        cin >> choice;
        if (choice == 1) {
            if (currentPlayer == 1) {
                player1->setScore(player1->getScore() + 2);
            } else {
                player2->setScore(player2->getScore() + 2);
            }
            deck->setCard(row1, col1, nullptr);
            deck->setCard(row2, col2, nullptr);
        } else {
            if (currentPlayer == 1) {
                player1->setScore(player1->getScore() + 1);
            } else {
                player2->setScore(player2->getScore() + 1);
            }
            // Do not switch player, allow the current player to take another turn
            deck->setCard(row1, col1, nullptr);
            deck->setCard(row2, col2, nullptr);
            switchPlayer();
            return;
        }
    } else {
        // Cards do not match, flip them back
        cout << "Cards do not match. Next player's turn." << endl;
        card1->setVisible(false);
        card2->setVisible(false);
    }
}

bool Game::checkGameOver() const {
    for (int i = 0; i < deck->getGridRows(); ++i) {
        for (int j = 0; j < deck->getGridCols(); ++j) {
            if (deck->getCard(i, j) != nullptr) {
                return false;
            }
        }
    }
    return true;
}

void Game::displayGrid() const {
    deck->displayGrid();
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

void Game::endGame() {
    cout << "Game Over!" << endl;
    int score1 = player1->getScore();
    int score2 = player2->getScore();

    cout << "Player 1 (Alice) score: " << score1 << endl;
    cout << "Player 2 (Bob) score: " << score2 << endl;

    if (score1 > score2) {
        cout << "Player 1 (Alice) wins!" << endl;
    } else if (score2 > score1) {
        cout << "Player 2 (Bob) wins!" << endl;
    } else {
        cout << "The game ends in a tie!" << endl;
    }
}

int Game::getCurrentPlayer() const {
    return currentPlayer;
}

void Game::printGrid() const {
    for (int i = 0; i < deck->getGridRows(); i++) {
        for (int j = 0; j < deck->getGridCols(); j++) {
            Card* card = deck->getCard(i, j);
            if (card != nullptr) {
                if (card->isVisible()) {
                    cout << card->getChar() << "  ";
                } else {
                    cout << "*  ";
                }
            } else {
                cout << "X  "; // Display empty space for removed cards
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