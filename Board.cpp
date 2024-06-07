#include "Board.hpp"
#include "Hexigon.hpp"
#include "Vertice.hpp"

Board::Board()
{
    vertices.resize(54); // Resize the vector to hold 54 elements
    for (int i = 0; i < 54; i++)
    {
        vertices[i] = new Vertice(i); // Create a new vertex and add it to the vector
    }
    hexigons.resize(36); // Resize the vector to hold 19 elements
    hexigons[0] = new Hexigon(ResourceType::ore, 10, {1, 2, 3, 9, 8, 7}, &vertices);
    hexigons[1] = new Hexigon(ResourceType::wool, 2, {3, 4, 5, 11, 10, 9}, &vertices);
    hexigons[2] = new Hexigon(ResourceType::lumber, 9, {5, 6, 7, 13, 12, 11}, &vertices);
    hexigons[3] = new Hexigon(ResourceType::grain, 12, {7, 8, 18, 17, 16, 14}, &vertices);
    hexigons[4] = new Hexigon(ResourceType::brick, 6, {8, 9, 10, 20, 19, 18}, &vertices);
    hexigons[5] = new Hexigon(ResourceType::wool, 4, {10, 11, 12, 22, 21, 20}, &vertices);
    hexigons[6] = new Hexigon(ResourceType::brick, 10, {12, 13, 15, 22, 23, 24}, &vertices);
    hexigons[7] = new Hexigon(ResourceType::grain, 9, {25, 16, 17, 29, 28, 27}, &vertices);
    hexigons[8] = new Hexigon(ResourceType::lumber, 11, {17, 18, 19, 31, 30, 29}, &vertices);
    hexigons[9] = new Hexigon(ResourceType::None, 0, {19, 20, 21, 33, 32, 31}, &vertices);
    hexigons[10] = new Hexigon(ResourceType::lumber, 3, {21, 22, 23, 33, 34, 35}, &vertices);
    hexigons[11] = new Hexigon(ResourceType::ore, 8, {23, 24, 26, 37, 36, 35}, &vertices);
    hexigons[12] = new Hexigon(ResourceType::lumber, 8, {28, 29, 30, 40, 39, 38}, &vertices);
    hexigons[13] = new Hexigon(ResourceType::ore, 3, {30, 31, 32, 42, 41, 40}, &vertices);
    hexigons[14] = new Hexigon(ResourceType::grain, 4, {32, 33, 34, 42, 43, 44}, &vertices);
    hexigons[15] = new Hexigon(ResourceType::wool, 5, {34, 35, 36, 44, 45, 46}, &vertices);
    hexigons[16] = new Hexigon(ResourceType::brick, 5, {39, 40, 41, 47, 48, 49}, &vertices);
    hexigons[17] = new Hexigon(ResourceType::grain, 6, {41, 42, 43, 49, 50, 51}, &vertices);
    hexigons[18] = new Hexigon(ResourceType::wool, 11, {43, 44, 45, 51, 52, 53}, &vertices);
    hexigons[19] = new Hexigon(ResourceType::sea, 1, {2, 1}, &vertices);
    hexigons[20] = new Hexigon(ResourceType::sea, 2, {1, 7, 14}, &vertices);
    hexigons[21] = new Hexigon(ResourceType::sea, 3, {14, 16, 25}, &vertices);
    hexigons[22] = new Hexigon(ResourceType::sea, 4, {25, 27}, &vertices);
    hexigons[23] = new Hexigon(ResourceType::sea, 5, {27, 28, 38}, &vertices);
    hexigons[24] = new Hexigon(ResourceType::sea, 6, {38, 39, 47}, &vertices);
    hexigons[25] = new Hexigon(ResourceType::sea, 7, {47, 48}, &vertices);
    hexigons[26] = new Hexigon(ResourceType::sea, 8, {48, 49, 50}, &vertices);
    hexigons[27] = new Hexigon(ResourceType::sea, 9, {50, 51, 52}, &vertices);
    hexigons[28] = new Hexigon(ResourceType::sea, 10, {52, 53}, &vertices);
    hexigons[29] = new Hexigon(ResourceType::sea, 11, {53, 45, 46}, &vertices);
    hexigons[30] = new Hexigon(ResourceType::sea, 12, {46, 36, 37}, &vertices);
    hexigons[31] = new Hexigon(ResourceType::sea, 13, {37, 26}, &vertices);
    hexigons[32] = new Hexigon(ResourceType::sea, 14, {26, 24, 15}, &vertices);
    hexigons[33] = new Hexigon(ResourceType::sea, 15, {15, 13, 7}, &vertices);
    hexigons[34] = new Hexigon(ResourceType::sea, 16, {7, 6}, &vertices);
    hexigons[35] = new Hexigon(ResourceType::sea, 17, {6, 5, 4}, &vertices);
    hexigons[36] = new Hexigon(ResourceType::sea, 18, {4, 3, 2}, &vertices);
}

Hexigon *Board::getHexigon(std::string type, int number)
{

    for (int i = 0; i < 37; i++)
    {
        if (gethexigonsboard()[i]->getType() == type && hexigons[i]->getNumber() == number)
        {
            return gethexigonsboard()[i];
        }
    }
    throw std::invalid_argument("Hexigon not found");
}

void Board::printBoard()
{
    for (int i = 0; i < 19; i++)
    {
        std::cout << "Hexigon " << i << " type: " << hexigons[i]->getType() << " number: " << hexigons[i]->getNumber() << std::endl;
    }
}

// Board::~Board()
// {
//     for (int i = 0; i < 54; i++)
//     {
//         delete vertices[i];
//     }

//     for (int i = 0; i < 36; i++)
//     {
//         delete hexigons[i];
//     }
//} // Destructor
