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
    std::vector<Cards> hand;
    std::vector<Cards> eat;
public:
    Player();
    void setName(std::string);
    std::string getName();
    void setHand(int, int, std::vector<Cards>&);
    void printHand();
    void sort();
};

class Game: public Player{ // game's structure and procedure
    std::vector<Cards> cards;
    int numOfPlayers; // number of players
    int banker;
    std::vector<Player> players; // the players
public:
    Game(): numOfPlayers(0), banker(-1) {};
    void printCards();
    void addCard(Cards);
    void shuffle();
    void setNumOfPlayers(int);
    void insertPlayer(Player);
    void getPlayer();
    void deal();
};

#endif