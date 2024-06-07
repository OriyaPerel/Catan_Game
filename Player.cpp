#include "Player.hpp"
#include "Board.hpp"
using namespace std;

// Player::~Player(){
//     for (Vertice *v : placesOfPlayer)
//     {
//         delete v;
//     }
//     for (Edge *e : roads)
//     {
//         delete e;
//     }

// }

int Player::getAmountOfResource(ResourceType resource) const
{
    if (resources.find(resource) != resources.end())
    {
        return resources.at(resource);
    }
    else
    {

        return 0;
    }
}

void Player::printRoads() const
{
    cout << name << " has the following roads: " << endl;
    for (Edge *e : roads)
    {
        cout << e->toString() << endl;
    }
}
void Player::printPlaces() const
{
    cout << name << " has the following settlements: " << endl;
    for (Vertice *v : placesOfPlayer)
    {
        cout << v->toString() << endl;
    }
}

void Player::printResources() const
{
    for (const auto &resource : resources)
    {
        cout << "Resource: " << resource.first << ", Amount: " << resource.second << endl;
    }
}

void Player::printPoints() const
{
    cout << "Player " << name << " has " << points << " points" << endl;
}

void Player::RemoveOraddResource(ResourceType resource, int count)
{
    resources[resource] += count;
}

int Player::getAmountOfResources() const
{
    int sum = 0;
    for (const auto &resource : resources)
    {
        sum += resource.second;
    }
    return sum;
}

void Player::removeMaxResource()
{
    int max = 0;
    ResourceType maxResource;
    for (const auto &resource : resources)
    {
        if (resource.second > max)
        {
            max = resource.second;
            maxResource = resource.first;
        }
    }
    RemoveOraddResource(maxResource, -1);
}

Vertice *findCommonVertexInBoard(const Hexigon &h1, const Hexigon &h2, const Hexigon &h3)
{
    // Get the vertices of each hexagon
    std::vector<Vertice *> vertices1 = h1.getVertices();
    std::vector<Vertice *> vertices2 = h2.getVertices();
    std::vector<Vertice *> vertices3 = h3.getVertices();

    // Iterate over the vertices of the first hexagon
    for (Vertice *v1 : vertices1)
    {
        // Check if v1 is also in the second and third hexagons
        if (v1 != nullptr &&
            std::find(vertices2.begin(), vertices2.end(), v1) != vertices2.end() &&
            std::find(vertices3.begin(), vertices3.end(), v1) != vertices3.end())
        {
            // If v1 is in all three hexagons, return it
            return v1;
        }
    }

    // If no common vertex is found, return nullptr
    return nullptr;
}

bool hasNeighbour(Vertice *v, std::vector<Edge *> h1e, std::vector<Edge *> h2e, std::vector<Edge *> h3e)
{
    // std::cout<<"the neighbours of the vertex:"<<v->getid()<<std::endl;
    for (Edge *e : h1e)
    {
        if (e->thisVerticeInEdge(v) && (e->getOtherVertice(v)->getisSettlement() == true))
        {
            // std::cout<<e->toString()<<std::endl;
            return true;
        }
    }
    for (Edge *e : h2e)
    {
        if (e->thisVerticeInEdge(v) && e->getOtherVertice(v)->getisSettlement() == true)
        {
            //  std::cout<<e->toString()<<std::endl;
            return true;
        }
    }
    for (Edge *e : h3e)
    {
        if (e->thisVerticeInEdge(v) && e->getOtherVertice(v)->getisSettlement() == true)
        {
            return true;
        }
    }
    return false;
}

bool Player::Has2RoadsBetween(Vertice *v)
{
    for (Edge *e : roads)
    {
        if (e->getV1() == v || e->getV2() == v && e->getEdgeOwner() == this)
        {
            Vertice *tmpVertex = e->getOtherVertice(v);
            for (Edge *e1 : roads)
            {
                if (e1->getV1() == tmpVertex || e1->getV2() == tmpVertex && e1->getEdgeOwner() == this)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void Player::placeSettelemnt(std::vector<std::string> places, std::vector<int> placesNum, Board &board)
{
    if (hisTurn == false)
    {
        throw std::invalid_argument("It's not your turn");
    }
    if (placesOfPlayer.size() >= 2 && (this->resources[ResourceType::brick] < 1 ||this-> resources[ResourceType::lumber] < 1 || this->resources[ResourceType::wool] < 1 || resources[ResourceType::grain] < 1))
    {
        throw std::invalid_argument("player can't buy a settlement");
    }
    Hexigon *hex1 = board.getHexigon(places[0], placesNum[0]);
    vector<Edge *> h1e = hex1->getEdges();
    Hexigon *hex2 = board.getHexigon(places[1], placesNum[1]);
    vector<Edge *> h2e = hex2->getEdges();
    Hexigon *hex3 = board.getHexigon(places[2], placesNum[2]);
    vector<Edge *> h3e = hex3->getEdges();
    Vertice *v = findCommonVertexInBoard(*hex1, *hex2, *hex3); // the common vertex of the three hexigons

    if (v == nullptr) // there is no common vertex
    {
        throw std::invalid_argument("There is no common vertex in this places");
    }

    if (v->getOwner() != NULL) // there are already a settlement in this vertex
    {
        throw std::invalid_argument("There is already a settlement in this vertex");
    }
    if (hasNeighbour(v, h1e, h2e, h3e) == true)
    {
        throw std::invalid_argument("There is already a settlement in this edge");
    }
    if (placesOfPlayer.size() >= 2 && Has2RoadsBetween(v) == false) // there are no 2 roads between the vertex and the player's settlements
    {
        throw std::invalid_argument("There are no 2 roads between the vertex and the player's settlements");
    }
    v->setOwner(this);
    v->setPieceType(PieceType::Settlement);
    v->setisSettlement(true);

    this->points += 1;
    if (this->placesOfPlayer.size() > 2)
    {
        RemoveOraddResource(ResourceType::brick, -1);
        RemoveOraddResource(ResourceType::lumber, -1);
        RemoveOraddResource(ResourceType::wool, -1);
        RemoveOraddResource(ResourceType::grain, -1);
    }
    else
    {
        RemoveOraddResource(ResourceType::brick, 1);
        RemoveOraddResource(ResourceType::lumber, 1);
        RemoveOraddResource(ResourceType::wool, 1);
        RemoveOraddResource(ResourceType::grain, 1);
    }
    this->placesOfPlayer.push_back(v); // add this settlement to the player's settlements
}


Edge *findCommonEdgeInBoard(const Hexigon &h1, const Hexigon &h2)
{
    // Get the edges of each hexagon
    std::vector<Edge *> edges1 = h1.getEdges();
    std::vector<Edge *> edges2 = h2.getEdges();

    // Iterate over the edges of the first hexagon
    for (Edge *e1 : edges1)
    {
        // Check if e1 is also in the second hexagon
        for (Edge *e2 : edges2)
        {
            if (e1->getV1() == e2->getV1() && e1->getV2() == e2->getV2() || e1->getV1() == e2->getV2() && e1->getV2() == e2->getV1())
            {
                return e1;
            }
        }
    }

    // If no common edge is found, return nullptr
    return nullptr;
}

bool hasEdgeNeighbour(Edge *e, std::vector<Edge *> roads)
{
    Vertice *v1 = e->getV1();
    Vertice *v2 = e->getV2();
    for (Edge *e1 : roads)
    {
        if (e1->getV1() == v1 || e1->getV2() == v1)
        {
            return true;
        }
    }
    for (Edge *e1 : roads)
    {
        if (e1->getV1() == v2 || e1->getV2() == v2)
        {
            return true;
        }
    }
    return false;
}

void Player::placeRoad(std::vector<std::string> places, std::vector<int> placesNum, Board Board)
{
    if (hisTurn == false)
    {
        throw std::invalid_argument("It's not your turn");
    }
    if (roads.size() > 2 && (this->resources[ResourceType::brick] < 1 || this->resources[ResourceType::lumber] < 1))
    {
        throw std::invalid_argument("player can't buy a road");
    }
    Hexigon *hex1 = Board.getHexigon(places[0], placesNum[0]);
    Hexigon *hex2 = Board.getHexigon(places[1], placesNum[1]);
    Edge *e = findCommonEdgeInBoard(*hex1, *hex2);
    if (e == nullptr)
    {
        throw std::invalid_argument("There is no common edge in this places");
    }
    if (e->getEdgeOwner() != NULL)
    {
        throw std::invalid_argument("There is already a road in this edge");
    }
    if (roads.size() < 2 && e->getV1()->getOwner() != this && e->getV2()->getOwner() != this)
    // in tha start its ok to put a road in a edge that not in routh of the player
    {
        throw std::invalid_argument("There is no settlement in this edge");
    }

    if (roads.size() >=2 && hasEdgeNeighbour(e, roads) == false)
    {
        throw std::invalid_argument("There is not a path to this edge");
    }
    e->setEdgeOwner(this);

    if (roads.size() > 2)
    {
        RemoveOraddResource(ResourceType::brick, -1);
        RemoveOraddResource(ResourceType::lumber, -1);
    }
    this->roads.push_back(e);
}

void Player::chengeSettlementToCity(std::vector<std::string> places, std::vector<int> placesNum, Board &board)
{
    if (this->hisTurn == false)
    {
        throw std::invalid_argument("It's not your turn");
    }
    if (this->resources[ResourceType::ore] < 3 || this->resources[ResourceType::grain] < 2)
    {
        throw std::invalid_argument("player can't buy a city");
    }
    Hexigon *hex1 = board.getHexigon(places[0], placesNum[0]);
    Hexigon *hex2 = board.getHexigon(places[1], placesNum[1]);
    Hexigon *hex3 = board.getHexigon(places[2], placesNum[2]);

    Vertice *v = findCommonVertexInBoard(*hex1, *hex2, *hex3); // the common vertex of the three hexigons
    if (v == nullptr) // there is no common vertex
    {
        throw std::invalid_argument("There is no common vertex in this places");
    }

     if (v->getOwner() != this) // there are already a settlement in this vertex
    {
        throw std::invalid_argument("You can't chenge this settlment, it's not your");
    }

    v->setPieceType(PieceType::City);
    this->points += 1;
    RemoveOraddResource(ResourceType::grain, -2);
    RemoveOraddResource(ResourceType::ore, -3);
}

void Player::trade(Player *player, ResourceType give, ResourceType get, int amountget, int amountgive)
{
    if (hisTurn == false)
    {
        throw std::invalid_argument("It's not your turn");
    }
    if (this == player)
    {
        throw std::invalid_argument("You can't trade with yourself");
    }

    if (this->getAmountOfResource(give) < amountgive || player->getAmountOfResource(get) < amountget)
    {
        throw std::invalid_argument("You don't have enough resources to trade");
    }
    this->RemoveOraddResource(give, -amountgive);
    this->RemoveOraddResource(get, amountget);
    player->RemoveOraddResource(give, amountgive);
    player->RemoveOraddResource(get, -amountget);
}
