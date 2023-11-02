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
        int index = hand[i].getIndex();
        if(index > t) {
            t += 6;
            if(index > t) { i--; continue; }
            std::cout << std::endl;
        }
        if(index <= t) std::cout << i + 1 << "." << hand[i].getCard() << ", ";
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

Cards* Player::throwCard() {
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

int Player::canChow(Cards* prevCard, int &eatType) {
    int index = prevCard->getIndex();
    int group = index / 3, order = index % 3;
    bool sequence[28] = {false};
    for(int i = 0; i < hand.size(); i++) {
        int temp = hand[i].getIndex();
        sequence[temp] = true;
    }
    if(sequence[index]) return (eatType)? 4 : 3;
    sequence[index] = true; 
    if(index >= 24) {
        for(int i = 24; i <= 27; i++) {
            if(!sequence[i]) return 0;
        }
        return (eatType)? 4 : 3;
    }
    for(int i = group * 3; i < group * 3 + 3; i++) {
        if(!sequence[i]) return 0;
    }
    return (eatType)? 4 : 3;
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

Cards* Player::dealwithChow(Cards* prevCard) {
    bool type[2] = {false};
    int index = prevCard->getIndex(); // 要看牌是第幾張，還要處理士兵可以有選擇。
    int group = index / 3, order = index % 3;
    int target[3] = {-1, -1, -1}, pos[3] = {-1, -1, -1}, count = 0, samePos = 0;
    if(index >= 24) {
        for(int i = 24; i <= 27; i++) {
            if(i == index) continue;
            target[count++] = i;
        }
    }
    else {
        for(int i = group * 3; i < group * 3 + 3; i++) {
            if(i == index) continue;
            target[count++] = i;
        }
    }
    count = 0;
    for(int i = 0; i < hand.size(); i++) {
        int temp = hand[i].getIndex();
        if(temp == index) samePos = i, type[0] = true;
        if(temp == target[count]) pos[count++] = i;
    }
    if(count >= 2) type[1] = true;
    if(type[0] && type[1]) {
        std::cout << "1. use same card, 2. use others cards:";
        int choice = makeDecision(1, 2);
        if(choice == 1) type[1] = false;
        else type[0] = false;
    }
    if(type[1] && index >= 24) {
        int types = 4;
        if(pos[0] == -1 || pos[1] == -1 || pos[2] == -1) types = 1;
        if(types == 4) {
            std::cout << "choose cards you want to use." << std::endl;
            std::string one = hand[pos[0]].getCard(), two = hand[pos[1]].getCard(), three = hand[pos[2]].getCard();
            std::cout << "1. " << one << '+' << two << ", 2. " << one << '+' << three << ", 3. "<< two << '+' << three << ", 4. " << one << '+' << two << '+' << three << ":";
            int choice = makeDecision(1,4);
            if(choice == 2) pos[1] = pos[2], pos[2] = -1;
            else if (choice == 3) pos[0] = pos[1], pos[1] = pos[2], pos[2] = -1;
        }
    }
    if(type[0]) {
        eat.push_back(hand[samePos]);
        hand.erase(hand.begin() + samePos);
    }
    else if(type[1]) {
        eat.push_back(hand[pos[0]]);
        hand.erase(hand.begin() + pos[0]);
        pos[1]--;
        eat.push_back(hand[pos[1]]);
        hand.erase(hand.begin() + pos[1]);
        if(pos[2] != -1) {
            pos[2] -= 2;
            eat.push_back(hand[pos[2]]);
            hand.erase(hand.begin() + pos[2]);
        }
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

int Game::decideToPlay() {
    int turn = 0, player = banker, count = 0;
    while(turn++ < numOfPlayers) {
        if(!count && turn == numOfPlayers) {
            count++;
            attend[player] = 1;
            break;
        }
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
        shuffle();
    }
    return count;
}

void Game::decideEatorNot(Cards* prevCard) {
    players[eatPlayer].printHand();
    std::string type[5] = {"", "1. Kai", "1. Pong, 2.no:", "1. Chow, 2.no:", "1. Pong, 2. Chow, 3.no:"};
    std::cout << players[eatPlayer].getName() << " want to eat " << prevCard->getCard() << '?' << std::endl;
    std::cout << type[eatType];
    int choice = 0;
    if(eatType == 1) {
        choice = players[eatPlayer].makeDecision(1, 1);
        player = eatPlayer;
        decideToEat = true;
    }
    if(eatType == 4) {
        choice = players[eatPlayer].makeDecision(1, 3);
        if(choice == 3) eatType = 0;
        else {
            eatType = choice + 1;
            player = eatPlayer;
            decideToEat = true;
        }
    }
    else {
        choice = players[eatPlayer].makeDecision(1, 2);
        if(choice == 2) eatType = 0;
        else {
            player = eatPlayer;
            decideToEat = true;
        }
    } 
}

void Game::start() {
    std::cout << "Game Start!" << std::endl;
    player = banker;
    Cards *prevCard = new Cards();
    while(attend[player] != 1) {
        if (++player == numOfPlayers) player = 0;
    }
    if(player == banker) {
        prevCard = players[player].throwCard();
        draw = true;
    }
    while(!win && stack.size() > 0) {
        int turn = draw ? 0 : 1;
        if(turn && ++player == numOfPlayers) player = 0;
        while(attend[player] != 1) {
            if (++player == numOfPlayers) player = 0;
            turn++;
        }
        eatType = 0, eatPlayer = player; // 看是否有吃碰，沒吃碰就摸牌、有吃碰就打牌
        decideToEat = false;
        while(turn++ < numOfPlayers) {
            if(attend[eatPlayer] != 1) {
                if (++eatPlayer == numOfPlayers) eatPlayer = 0;
                continue;
            }
            eatType = players[eatPlayer].canKaiOrPong(prevCard);
            if(eatType) break;
            if (++eatPlayer == numOfPlayers) eatPlayer = 0;
        }
        // [沒有人可以開或碰] 或是 [可以碰的是下家(可以開的話一定要開)]就要看可不可以吃。
        if(!eatType || (eatPlayer == player && eatType == 2)) {
            eatType = players[player].canChow(prevCard, eatType); // return 4 如果可以碰加吃。
            if(eatType) eatPlayer = player;
        }
        if(eatType) {
            decideEatorNot(prevCard);
        }
        if(!eatType && draw) { // 如果上一回合的牌是用摸的且摸的人沒有要吃碰的話，
            int next = player;
            if (++next == numOfPlayers) next = 0;
            while(attend[next] != 1) {
                if (++next == numOfPlayers) next = 0;
            }
            eatType = players[next].canChow(prevCard, eatType);
            if(eatType) {
                eatPlayer = next;
                decideEatorNot(prevCard);
            }
        } 
        if(!decideToEat) {
            if(draw && ++player == numOfPlayers) player = 0;
            while(attend[player] != 1) {
                if (++player == numOfPlayers) player = 0;
            }
            prevCard = players[player].drawCard(stack);
            draw = true;
        }
        else {
            if (eatType == 3) prevCard = players[player].dealwithChow(prevCard);
            else prevCard = players[player].dealwithEat(eatType, prevCard);
            draw = false;
        }
        std::cout << player << " " << stack.size() << std::endl;
    }
    delete [] prevCard;
}