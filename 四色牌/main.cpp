#include "fourColor.h"
std::string Name[6] = {"p1", "p2", "p3", "p4", "p5", "p6"};
std::string types[7] = {"general", "advisor", "elephant", "horse", "chariot", "cannon", "soldier"};
std::string colors[4] = {"red", "green", "yellow", "white"};

int main(int argc, char *argv[])
{   
    Game *game = new Game();
    int c = 0, t = 0;
    for(int i = 0; i < CARD_NUMBER; i++) {
        if(i % 4 == 0 & i != 0) t++;
        if(t == 7) c++, t = 0;
        Cards card(i, colors[c] + ' ' + types[t], 0);
        game->addCard(card);
    }
    game->shuffle();
    //game->printCards();

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
    game->getPlayer();

    game->deal();
}