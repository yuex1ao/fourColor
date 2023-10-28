#include "fourColor.h"
std::string Name[6] = {"p1", "p2", "p3", "p4", "p5", "p6"};
std::string types[7] = {"general", "advisor", "elephant", "chariot", "horse", "cannon", "soldier"};
std::string colors[4] = {"red", "green", "yellow", "white"};
int INDEX[28] = {0,1,2,3,4,5,24,6,7,8,9,10,11,25,12,13,14,15,16,17,26,18,19,20,21,22,23,27};

int main(int argc, char *argv[])
{   
    /*int operation = 0;
    std::cout << "Welcome to the game of 4-color!" << std::endl;
    std::cout << "Please choose an operation:" << std::endl;
    std::cout << "1. Play, 2. Exit" << std::endl;
    while(std::cin >> operation) {
        if(operation < 1 || operation > 2) {
            std::cout << "Invalid operation, try again:" << std::endl;
            continue;
        }
        if(operation == 2) {
            std::cout << "Thank you for playing!" << std::endl;
            break;
        }*/

        Game *game = new Game();
        std::cout << "enter the number of players (2~6):";
        int p = 0;
        while(std::cin >> p) {
            if(p >= 2 && p <= 6) break;
            std::cout << "invalid input, try again:";
        }
        game->setNumOfPlayers(p);
        for(int i = 0; i < p; i++) {
            Player player;
            player.setName(Name[i]);
            game->insertPlayer(player);
        }
        //game->getPlayer();

        // game statd, first step is to deal with cards
        int c = 0, t = 0, index = 0;
        for(int i = 0; i < CARD_NUMBER; i++) {
            if(i % 4 == 0 & i != 0) t++, index++;
            if(t == 7) c++, t = 0;
            Cards card(INDEX[index], colors[c] + ' ' + types[t]);
            game->addCard(card);
        }
        game->shuffle();
        //game->printCards();
        game->deal();
        game->decideToPlay();
        game->start();

        delete[] game;
    //}
}