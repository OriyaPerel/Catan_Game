#include "Hexigon.hpp"

Hexigon::Hexigon(ResourceType type, int number, std::vector<int> hisVertices, std::vector<Vertice *> *Allvertices)
    : type(type), number(number), vertices(hisVertices.size(), nullptr)
{
    std::vector<Vertice *> &tmp = *Allvertices;
    for (int i = 0; i < hisVertices.size(); i++)
    {
        int index = hisVertices[i];
        Vertice *vertice = tmp[index];
        vertices[i] = vertice;
    }

    for (int i = 0; i < hisVertices.size() - 1; i++)
    {
        int index1 = hisVertices[i];
        int index2 = hisVertices[i + 1];
        if (index1 >= 0 && index1 < Allvertices->size() && index2 >= 0 && index2 < Allvertices->size())
        {
            Edge *edge = new Edge((*Allvertices)[index1], (*Allvertices)[index2]);
            this->edges.push_back(edge);
        }
    }
    if (ResourceType::sea != type)
    {
        int index1 = hisVertices[0];
        int index2 = hisVertices[hisVertices.size() - 1];
        if (index1 >= 0 && index1 < Allvertices->size() && index2 >= 0 && index2 < Allvertices->size())
        {
            Edge *edge = new Edge((*Allvertices)[index1], (*Allvertices)[index2]);
            this->edges.push_back(edge);
        }
    }
}

Hexigon::~Hexigon()
{
    if (edges.size() > 0){
    for(auto e : edges) {
        delete e;
    }
    }
}

std::string Hexigon::getType() const
{
    switch (type)
    {
    case ResourceType::None:
        return "None";
    case ResourceType::brick:
        return "brick";
    case ResourceType::lumber:
        return "lumber";
    case ResourceType::ore:
        return "ore";
    case ResourceType::grain:
        return "grain";
    case ResourceType::wool:
        return "wool";
    case ResourceType::sea:
        return "sea";

    default:
        return "unknown";
    }
}

void Hexigon::toString() const
{
    std::cout << "Type:" << getType() << " Number: " << this->number << std::endl;
}

void Hexigon::printVertices() const
{
    for (Vertice *v : vertices)
    {
        if (v != nullptr)
        {
            std::cout << v->getid() << " ";
        }
        else
        {
            std::cout << "null ";
        }
    }
    std::cout << std::endl;
}

void Hexigon::printEdges() const
{
    for (Edge *e : edges)
    {
        std::cout << e->toString() << std::endl;
    }
}



std::ostream& operator<<(std::ostream& os, const ResourceType& resourceType) {
    switch (resourceType) {
        case ResourceType::wool:
            os << "Wool";
            break;
        case ResourceType::brick:
            os << "Brick";
            break;
        case ResourceType::lumber:
            os << "Lumber";
            break;
        case ResourceType::grain:
            os << "grain";
            break;
        case ResourceType::ore:
            os << "Ore";
            break;
        default:
            os << "Unknown";
            break;
    }
    return os;
}
