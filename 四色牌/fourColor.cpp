#include "fourColor.h"

// Cards
Cards::Cards(int index, std::string card, int position) {
    this->index = index;
    this->card = card;
    this->position = position;
}

std::string Cards::getCard() {
    return card;
}
int Cards::getIndex() {
    return index;
}
int Cards::getPosition() {
    return position;
}


// Player
Player::Player() {}

void Player::setName(std::string name) {
    this->name = name;
}
std::string Player::getName() {
    return this->name;
}


// Game
void Game::printCards() {
    for(int i = 0; i < CARD_NUMBER; i++) {
        std::cout << cards[i].getIndex() << " " << cards[i].getCard() << std::endl;
    }
}

void Game::addCard(Cards card) {
    this->cards.push_back(card);
}

void Game::shuffle() {
    srand((unsigned)time(NULL));
    for (int i = 0; i < CARD_NUMBER; i++) {
        int n = rand() % (CARD_NUMBER - i) + i;
        std::swap(cards[i], cards[n]);
    }
}

void Game::setNumOfPlayers(int numOfPlayers) {
    this->numOfPlayers = numOfPlayers;
    banker = rand() % numOfPlayers;
}

void Game::insertPlayer(Player player) {
    this->players.push_back(player);
}

void Game::getPlayer() {
    for(auto &i: this->players) {
        std::cout << i.getName() << std::endl;
    }
}

void Game::deal() { // DO
    
}