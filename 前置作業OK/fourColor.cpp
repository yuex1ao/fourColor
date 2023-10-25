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
void Cards::setPosition(int pos) {
    this->position = pos;
}
int Cards::getPosition() {
    return position;
}



// Player
Player::Player() { this->money = 10000; }

void Player::setName(std::string name) {
    this->name = name;
}
std::string Player::getName() {
    return this->name;
}

void Player::setHand(int count, std::vector<Cards> &board, int pos) {
    while(count--) {
        this->hand.push_back(board.back());
        board.back().setPosition(pos);
        board.pop_back();
    }
}
void Player::printHand() {
    std::cout << std::endl;
    int t = 5;
    for(auto &i: this->hand) {
        if(i.getIndex() > t) {
            t += 6;
            std::cout << std::endl;
        }
        std::cout << " " << i.getCard() << ",";
    }
    std::cout << std::endl << std::endl;
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

void Player::returnToBoard(std::vector<Cards> &board) {
    board.insert(board.end(), this->hand.begin(), this->hand.end());
    hand.clear();
}



// Game
void Game::setMoney(int base, int flower, int giveUp) {
    this->base = base;
    this->flower = flower;
    this->giveUp = giveUp;
}

void Game::printCards() {
    for(int i = 0; i < CARD_NUMBER; i++) {
        std::cout << board[i].getIndex() << " " << board[i].getCard() << std::endl;
    }
}

void Game::addCard(Cards card) {
    this->board.push_back(card);
}

void Game::shuffle() {
    srand((unsigned)time(NULL));
    int size = board.size();
    for (int i = 0; i < size; i++) {
        int n = rand() % (size - i) + i;
        std::swap(board[i], board[n]);
    }
}

void Game::setNumOfPlayers(int numOfPlayers) {
    srand((unsigned)time(NULL));
    this->numOfPlayers = numOfPlayers;
    banker = rand() % numOfPlayers;
    attend.clear();
    attend.resize(numOfPlayers, 0);
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
    int turn = 3 * numOfPlayers - 1, count = 7, player = banker;
    players[player].setHand(count, board, player);
    count = 6;
    while(turn--) {
        if (++player == numOfPlayers) player = 0;
        players[player].setHand(count, board, player);
    }
    for(auto &i: players) {
        i.sort();
    }
}

void Game::decideToPlay() {
    int turn = 0, player = banker, count = 0;
    while(turn++ < numOfPlayers) {
        if(count == 5) {
            attend[player] = 3;
            break;
        }
        players[player].printHand();
        std::cout << players[player].getName() << " want to play?\n1.attend, 2.pass:";
        int choice = 0;
        while(std::cin >> choice) {
            if(choice >= 1 && choice <= 2) break;
            std::cout << "Please input 1 or 2, try again:";
        }
        attend[player] = choice;
        if(choice == 1) count++;
        if (++player == numOfPlayers) player = 0;
    }
    if(numOfPlayers == 6) { // 六人遊玩時第一個放棄的要把牌放回board
        player = banker;
        while(attend[player] == 1) {
            if (++player == numOfPlayers) player = 0;
        }
        players[player].returnToBoard(board);
    }
    shuffle();
}

void Game::start() {
    std::cout << "Game Start!" << std::endl;
}