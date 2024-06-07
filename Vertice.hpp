
#ifndef VERTICE_HPP
#define VERTICE_HPP
class Hexigon; // Forward declaration
#include "Player.hpp"

enum class PieceType
{
    None,
    Settlement,
    City,
};

class Vertice
{
private:
    PieceType pieceType;
    int Id;
    bool isSettlement;
    Player *owner;

public:
    Vertice(int id);
    //~Vertice();
    int getid() { return Id; }
    void setPieceType(PieceType pieceType) { this->pieceType = pieceType; }
    bool getisSettlement() { return isSettlement; }
    void setisSettlement(bool isSettlement) { this->isSettlement = isSettlement; }
    void setOwner(Player *owner) { this->owner = owner; }
    Player *getOwner() { return owner; }
    std::string pieceTypeToString(PieceType pieceType);
    std::string getPieceType() { return pieceTypeToString(pieceType); }
    std::string toString();
};
#endif
