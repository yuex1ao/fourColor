#include "fourColor.h"

// Cards
Cards::Cards(int index, std::string card) {
    this->index = index;
    this->card = card;
}

std::string Cards::getCard() {
    return card;
}
int Cards::getIndex() {
    return index;
}



// Player
Player::Player() { this->money = MONEY; }

void Player::setName(std::string name) {
    this->name = name;
}
std::string Player::getName() {
    return this->name;
}

void Player::setHand(int count, std::vector<Cards> &stack, int pos) {
    while(count--) {
        this->hand.push_back(stack.back());
        stack.pop_back();
    }
}
void Player::printHand() {
    std::cout << std::endl;
    int t = 5;
    for(int i = 0; i < this->hand.size(); i++) {
        if(hand[i].getIndex() > t) {
            t += 6;
            std::cout << std::endl;
        }
        std::cout << i + 1 << "." << hand[i].getCard() << ", ";
    }
    std::cout << std::endl << std::endl;
}

int Player::makeDecision(int lower, int upper) {
    int choice = 0;
    while(std::cin >> choice) {
        if(choice >= lower && choice <= upper) return choice;
        printf("Please enter a number between %d and %d, try again:", lower, upper);
    }
    return 0;
}
int Player::makeDecision(int lower, int upper, int *general) {
    int choice = 0;
    while(std::cin >> choice) {
        if(choice >= lower && choice <= upper) {
            int index = hand[choice - 1].getIndex();
            if(index == general[0] || index == general[1] || index == general[2] || index == general[3]) {
                std::cout << "General card cannot be throw!, try again:";
                continue;
            }
            return choice;
        }
        printf("Please enter a number between %d and %d, try again:", lower, upper);
    }
    return 0;
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

void Player::returnToBoard(std::vector<Cards> &stack) {
    stack.insert(stack.end(), this->hand.begin(), this->hand.end());
    hand.clear();
}

Cards* Player::throwCard() { // 在考慮要不要加上只有一支兵一定要打，不過好像沒關係因為留著也沒用。
    printHand();
    int general[4] = {0, 6, 12, 18};
    std::cout << getName() << " Choose the number of card which you want to discard:";
    int choice = makeDecision(1, hand.size(), general);
    discard.push_back(hand[choice - 1]);
    hand.erase(hand.begin() + choice - 1);
    return &discard.back();
}

Cards* Player::drawCard(std::vector<Cards> &stack) {
    int index = stack.back().getIndex();
    if(index == 0 || index == 6 || index == 12 || index == 18){
        eat.push_back(stack.back());
        stack.pop_back();
        std::cout << eat.back().getCard() << std::endl;
        return throwCard();
    }
    else {
        discard.push_back(stack.back());
        stack.pop_back();
        std::cout << discard.back().getCard() << std::endl;
        return &discard.back();
    }
}

int Player::canKaiOrPong(Cards* prevCard) {
    int index = prevCard->getIndex(), count = 0;
    for(int i = 0; i < hand.size(); i++) {
        if(hand[i].getIndex() == index) count++;
    }
    if(count == 3) return 1;
    else if (count == 2) return 2;
    return 0;
}

int Player::canChow(Cards* prevCard) {
    int index = prevCard->getIndex();
    int group = index / 3, order = index % 3;
    bool sequence[3] = {false};
    for(int i = 0; i < hand.size(); i++) {
        int temp = hand[i].getIndex();
        if(temp / 3 == group) {
            sequence[temp % 3] = true;
        }
    }
    for(int i = 0; i < 3; i++) {
        if(!sequence[i]) return 0;
    }
    return 3;
}

Cards* Player::dealwithEat(int eatType, Cards* prevCard) {
    int index = prevCard->getIndex(), pos = 0;
    for(int i = 0; i < hand.size(); i++) {
        if(hand[i].getIndex() == index) {
            pos = i;
            break;
        }
    }
    eat.push_back(hand[pos]);
    hand.erase(hand.begin() + pos);
    eat.push_back(hand[pos]);
    hand.erase(hand.begin() + pos);
    if(eatType == 1) {
        eat.push_back(hand[pos]);
        hand.erase(hand.begin() + pos);
    }
    eat.push_back(*prevCard);
    prevCard = NULL;
    return throwCard();
}


// Game
void Game::setMoney(int base, int flower, int giveUp) {
    this->base = base;
    this->flower = flower;
    this->giveUp = giveUp;
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


void Game::printCards() {
    for(int i = 0; i < stack.size(); i++) {
        std::cout << stack[i].getIndex() << " " << stack[i].getCard() << std::endl;
    }
}

void Game::addCard(Cards card) {
    this->stack.push_back(card);
}

void Game::shuffle() {
    srand((unsigned)time(NULL));
    int size = stack.size();
    for (int i = 0; i < size; i++) {
        int n = rand() % (size - i) + i;
        std::swap(stack[i], stack[n]);
    }
}

void Game::deal() {
    int turn = 3 * numOfPlayers - 1, count = 7, player = banker;
    players[player].setHand(count, stack, player);
    count = 6;
    while(turn--) {
        if (++player == numOfPlayers) player = 0;
        players[player].setHand(count, stack, player);
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
        int choice = players[player].makeDecision(1, 2);
        attend[player] = choice;
        if(choice == 1) count++;
        if (++player == numOfPlayers) player = 0;
    }
    if(numOfPlayers == 6) { // 六人遊玩時第一個放棄的要把牌放回board
        player = banker;
        while(attend[player] == 1) {
            if (++player == numOfPlayers) player = 0;
        }
        players[player].returnToBoard(stack);
    }
    shuffle();
}

void Game::start() {
    std::cout << "Game Start!" << std::endl;
    bool win = false;
    int player = banker;
    Cards *prevCard = new Cards();
    while(attend[player] != 1) {
        if (++player == numOfPlayers) player = 0;
    }
    if(player == banker) {
        prevCard = players[player].throwCard();
    }
    while(!win && stack.size() > 0) {
        int turn = 0, eatType = 0, eatPlayer = player; // 看是否有吃碰(開:1, 碰:2, 吃:3)，沒吃碰就摸牌、有吃碰就打牌
        bool decideToEat = false;
        while(turn++ < numOfPlayers) {
            if(eatPlayer == player || attend[eatPlayer] != 1) {
                if (++eatPlayer == numOfPlayers) eatPlayer = 0;
                continue;
            }
            eatType = players[player].canKaiOrPong(prevCard);
            if(!eatType) break;
            if (++eatPlayer == numOfPlayers) eatPlayer = 0;
        }
        if (++player == numOfPlayers) player = 0; 
        while(attend[player] != 1) {
            if (++player == numOfPlayers) player = 0;
        }   
        if(!eatType || eatPlayer == player) { // [沒有人可以開或碰] 或是 [可以開或碰的是下家]就要看可不可以吃。
            players[player].canChow(prevCard);
        }
        if(eatType) {
            players[eatPlayer].printHand();
            std::cout << players[eatPlayer].getName() << " want to eat " << prevCard->getCard() << '?' << std::endl;
            std::cout << "1. eat, 2.no:";
            int choice = players[eatPlayer].makeDecision(1, 2);
            if(choice == 1) {
                player = eatPlayer;
                decideToEat = true;
            }
        }
        if(!decideToEat) prevCard = players[player].drawCard(stack);
        else {
            prevCard = players[player].dealwithEat(eatType, prevCard);
        }
        std::cout << player << " " << stack.size() << std::endl;
    }
    delete [] prevCard;
}