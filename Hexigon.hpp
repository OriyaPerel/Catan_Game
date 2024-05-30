
#ifndef HEXIGON_HPP
#define HEXIGON_HPP

#include <vector>
#include <iostream>
#include <string>
#include "Vertice.hpp"
#include "Edge.hpp"

enum class ResourceType
{
    None,   // Desert מדבר
    ore,    // Mountains ברזל אפור
    grain,  // Agricultural Land שיבולת
    wool,   // Pasture Landצמר ירוק בהיר
    brick,  // Hills לבנה הגבעות חום בהיר
    lumber, //  Forest עץ ירוק כהה
    sea,    // ים
};

class Hexigon
{
private:
    ResourceType type;
    int number;
    std::vector<Vertice *> vertices;
    std::vector<Edge *> edges;

public:
    Hexigon(ResourceType type, int number, std::vector<int> hisVertices, std::vector<Vertice *> *Allvertices);

    std::string getType() const;
    int getNumber() { return number; }

    std::vector<Vertice *> getVertices() const { return vertices; }
    std::vector<Edge *> getEdges() const { return edges; }

    void toString() const;
    void printVertices() const;
    void printEdges() const;
};
#endif