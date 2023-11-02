#ifndef FOURCOLOR_H
#define FOURCOLOR_H
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>

#define CARD_NUMBER 112
#define MONEY 10000

class Cards { // any card has it own object
    int index; // index of the card
    std::string card; // the card itself
public:
    Cards() {};
    Cards(int, std::string);
    std::string getCard();
    int getIndex();
};


class Player: public Cards{
    std::string name;
    int money;
    std::vector<Cards> hand;
    std::vector<Cards> eat;
    std::vector<Cards> discard;
public:
    Player();
    void setName(std::string);
    std::string getName();
    void setHand(int, std::vector<Cards>&, int);
    void printHand();
    int makeDecision(int, int);
    int makeDecision(int, int, int*);
    void sort();
    void returnToBoard(std::vector<Cards>&);
    Cards* throwCard(); // 打牌
    Cards* drawCard(std::vector<Cards>&); // 摸牌
    int canKaiOrPong(Cards*); // 四張同樣(一定要開，除非直接胡了), 三張同樣, 順
    int canChow(Cards*, int&); // 下家可以吃
    Cards* dealwithEat(int, Cards*);
    Cards* dealwithChow(Cards*);
};


class Game{ // game's structure and procedure
    int base;
    int flower;
    int giveUp;
    std::vector<Cards> stack;
    int numOfPlayers; // number of players
    int banker;
    std::vector<int> attend; // the players attend type -> 1: attend, 2: pass, 3: forced(被迫放棄)
    std::vector<Player> players; // the players
    // int the game
    int player;
    int eatPlayer;
    int eatType;
    bool decideToEat;
    bool win;
    bool draw;
public:
    Game(): base(100), flower(50), giveUp(50), numOfPlayers(0), banker(-1), player{-1}, eatPlayer{-1}, eatType{0}, decideToEat{false}, win{false}, draw{false} {};
    void setMoney(int, int, int);
    void setNumOfPlayers(int);
    void insertPlayer(Player);
    void getPlayer();
    void printCards();
    void addCard(Cards);
    void shuffle(); 
    void deal();
    int decideToPlay();
    void decideEatorNot(Cards*);
    void start();
};

#endif