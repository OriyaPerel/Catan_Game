#ifndef EDGE_HPP
#define EDGE_HPP
#include "Vertice.hpp"
#include "Player.hpp"

class Edge
{
private:
    Vertice *vertice1;
    Vertice *vertice2;
    Player *owner;

public:
    Edge(Vertice *vertice1, Vertice *vertice2);
    ~Edge(){}
    Vertice *getOtherVertice(const Vertice *v)const ;
    bool thisVerticeInEdge( const Vertice *v)const ;
    Vertice *getV1() const { return vertice1; }
    Vertice *getV2()const  { return vertice2; }
    Player *getEdgeOwner() const{ return owner; }
    void setEdgeOwner(Player *owner) { this->owner = owner; }
    std::string toString()const ;
};
#endif
