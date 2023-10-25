#ifndef FOURCOLOR_H
#define FOURCOLOR_H
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>

#define CARD_NUMBER 112

class Cards { // any card has it own object
    int index; // index of the card
    std::string card; // the card itself
    int position; // -1: board,  0 ~ numOfPlayer-1: hand,  numOfPlayer ~ 2*numOfPlayer-1: eat
public:
    Cards() {};
    Cards(int, std::string, int);
    std::string getCard();
    int getIndex();
    void setPosition(int);
    int getPosition();
};


class Player: public Cards{
    std::string name;
    int money;
    std::vector<Cards> hand;
    std::vector<Cards> eat;
public:
    Player();
    void setName(std::string);
    std::string getName();
    void setHand(int, std::vector<Cards>&, int);
    void printHand();
    void sort();
    void returnToBoard(std::vector<Cards>&);
};


class Game{ // game's structure and procedure
    int base;
    int flower;
    int giveUp;
    std::vector<Cards> board;
    int numOfPlayers; // number of players
    int banker;
    std::vector<int> attend; // the players attend type -> 1: attend, 2: pass, 3: forced(被迫放棄)
    std::vector<Player> players; // the players
public:
    Game(): base(100), flower(50), giveUp(50), numOfPlayers(0), banker(-1) {};
    void setMoney(int, int, int);
    void printCards();
    void addCard(Cards);
    void shuffle();
    void setNumOfPlayers(int);
    void insertPlayer(Player);
    void getPlayer();
    void deal();
    void decideToPlay();
    void start();
};

#endif