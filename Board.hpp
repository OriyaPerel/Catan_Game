#include "Hexigon.hpp"
#include "Vertice.hpp"
#include <vector>
#include <stdexcept>

#ifndef BOARD_HPP
#define BOARD_HPP
class Board
{
private:
    std::vector<Hexigon *> hexigons;
    std::vector<Vertice *> vertices;

public:
    Board();
    ~Board();
    Hexigon *getHexigon(std::string type, int number) const;
    std::vector<Hexigon *> gethexigonsboard() const { return hexigons; };
    std::vector<Vertice *> getverticesboard() const { return vertices; };
    std::string printVertice(int index) const;

    void printBoard() const;
};
#endif
