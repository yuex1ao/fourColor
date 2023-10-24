#ifndef FOURCOLOR_H
#define FOURCOLOR_H
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <random>

#define CARD_NUMBER 112

class Cards { // any card has it own object
    int index; // index of the card
    std::string card; // the card itself
    int position; // the position of the card in the deck
public:
    Cards() {};
    Cards(int, std::string, int);
    std::string getCard();
    int getIndex();
    int getPosition();
};

class Player: public Cards{
    std::string name;
    std::vector<Cards> hand; // 這樣寫的話要把每一張牌都當作一個物件
    std::vector<Cards> eat;
public:
    Player();
    void setName(std::string);
    std::string getName();
};

class Game{ // game's structure and procedure
    int numOfPlayers; // number of players
    int banker;
    std::vector<Player> players; // the players
    std::vector<Cards> cards; // the deck
public:
    Game(): numOfPlayers(0), banker(0) {};
    void printCards();
    void addCard(Cards);
    void shuffle();
    void setNumOfPlayers(int);
    int getNumOfPlayers();
    void insertPlayer(Player);
    void getPlayer();
    void deal();
};

#endif