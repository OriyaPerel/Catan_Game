#include <vector>
#include "Player.hpp"
#include "Board.hpp"


class Catan {
    private:
    std::vector<Player> players;
    Board board;

    public:
    Catan(Player p1, Player p2, Player p3);
    void ChooseStartingPlayer();
    Board& getBoard();
    void printWinner();
};