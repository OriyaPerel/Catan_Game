
#ifndef HEXIGON_HPP
#define HEXIGON_HPP
# // id:322522806
# // email:oriyaperel18@gmail.com

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
    ~Hexigon();
    std::string getType() const;
    ResourceType getResourceType() const { return type; }
    int getNumber() const{ return number; }

    std::vector<Vertice *> getVertices() const { return vertices; }
    std::vector<Edge *> getEdges() const { return edges; }

    void toString() const;
    void printVertices() const;
    void printEdges() const;
};
std::ostream &operator<<(std::ostream &os, const ResourceType &resourceType);
#endif
