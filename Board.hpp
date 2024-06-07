#include "Hexigon.hpp"
#include "Vertice.hpp"
#include <vector>
#include <stdexcept>

#ifndef BOARD_HPP
#define BOARD_HPP
class Board
{
public:
    Board();
   // ~Board();
    Hexigon *getHexigon(std::string type, int number);
    std::vector<Hexigon *> gethexigonsboard() { return hexigons; };
    std::vector<Vertice *> getverticesboard() { return vertices; };
    std::string printVertice(int index)
    {
        return vertices[index]->toString();
    };
    void printBoard();
    ResourceType getResourseofNumwithV(int number,Vertice *v);

private:
    std::vector<Hexigon *> hexigons;
    std::vector<Vertice *> vertices;
    
};
#endif
