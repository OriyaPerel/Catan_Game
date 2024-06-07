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
    //~Edge();
    Vertice *getOtherVertice(Vertice *v);
    bool thisVerticeInEdge(Vertice *v);
    Vertice *getV1() { return vertice1; }
    Vertice *getV2() { return vertice2; }
    Player *getEdgeOwner() { return owner; }
    void setEdgeOwner(Player *owner) { this->owner = owner; }
    std::string toString();
};
#endif
