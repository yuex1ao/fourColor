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

void Player::setHand(int begin, int end, std::vector<Cards> &cards) {
    for(begin; begin < end; begin++) {
        this->hand.push_back(cards[begin]);
    }
}
void Player::printHand() {
    for(auto &i: this->hand) {
        std::cout << i.getCard() << std::endl;
    }
}

void Player::sort() {
    for(int i = 1; i < hand.size(); i++) {
        int j = i;
        while(j > 0 && hand[j].getIndex() < hand[j - 1].getIndex()) {
            std::swap(hand[j], hand[j - 1]);
            j--;
        }
    }
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

void Game::deal() {
    int turn = 3 * numOfPlayers - 1, count = 0, player = banker;
    players[player].setHand(count, count + 7, cards);
    count += 7;
    while(turn--) {
        if (++player == numOfPlayers) player = 0;
        players[player].setHand(count, count + 6, cards);
        count += 6;
    }
    for(auto &i: players) {
        i.sort();
        std::cout << i.getName() << std::endl;
        i.printHand();
    }
}