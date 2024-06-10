
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
    ~Vertice(){}
    int getid() const{ return Id; }
    Player *getOwner() const{ return owner; }
    bool getisSettlement() const{ return isSettlement; }

    void setPieceType(PieceType pieceType) { this->pieceType = pieceType; }
    void setisSettlement(bool isSettlement) { this->isSettlement = isSettlement; }
    void setOwner(Player *owner) { this->owner = owner; }
    
    std::string pieceTypeToString(PieceType pieceType)const;
    std::string getPieceType() const{ return pieceTypeToString(pieceType); }
    std::string toString() const;
};
#endif
