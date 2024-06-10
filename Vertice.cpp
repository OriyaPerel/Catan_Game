#include "Vertice.hpp"
 // id:322522806
 // email:oriyaperel18@gmail.com

Vertice::Vertice(int id)
{
    this->pieceType = PieceType::None;
    this->Id = id;
    this->isSettlement = false;
}

std::string Vertice::pieceTypeToString(PieceType pieceType) const
{
    switch (pieceType)
    {
    case PieceType::City:
        return "City";
    case PieceType::None:
        return "None";
    case PieceType::Settlement:
        return "settlement";
    default:
        return "Unknown";
    }
}

std::string Vertice::toString()const
{
    if (owner == NULL)
    {
        return "Vertice id: " + std::to_string(Id) + " owner: " + "None" + " pieceType: " + getPieceType();
    }
    else
    {
        return "Vertice id: " + std::to_string(Id) + " pieceType: " + getPieceType();
    }
}
