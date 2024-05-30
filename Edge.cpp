#include "Edge.hpp"

Edge::Edge(Vertice *vertice1, Vertice *vertice2)
{
    this->vertice1 = vertice1;
    this->vertice2 = vertice2;
}

Vertice *Edge::getOtherVertice(Vertice *v)
{
    if (v == vertice1)
    {
        return vertice2;
    }
    return vertice1;
}

bool Edge::thisVerticeInEdge(Vertice *v)
{
    if (v == vertice1 || v == vertice2)
    {
        return true;
    }
    return false;
}
std::string Edge:: toString()
    {
        return "Edge:" + std::to_string(vertice1->getid()) + "-> " + std::to_string(vertice2->getid());
    }