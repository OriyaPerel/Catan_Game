#include "catan.hpp"
#include <iostream>
Catan::Catan(Player p1, Player p2, Player p3) {
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);
}

void Catan::ChooseStartingPlayer() {
    if (!players.empty()) {
        std::cout << players[0].getName() << std::endl;
    } else {
        std::cout << "No players available" << std::endl;
    }
}

Board& Catan::getBoard() {
    return board;
}