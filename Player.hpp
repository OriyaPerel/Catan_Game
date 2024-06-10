#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <map>

enum class ResourceType;
enum class CardType;
class Board;
class Edge;
class Vertice;
class Hexigon; // Forward declaration

class Player
{
private:
    std::string name;
    std::vector<Vertice *> placesOfPlayer;
    std::vector<Edge *> roads;
    std::map<ResourceType, int> resources;
    std::map<CardType, int> cards;
    int points = 0;
    bool hisTurn = false;

public:
    Player() = default;
    Player(std::string name) : name(name){};
    ~Player() {}
    std::string getName() const { return name; }
    int getPoints() const { return points; }
    std::map<CardType, int> getCardMap() const { return cards; }
    int getAmountOfResource(ResourceType resource) const;
    int getAmountOfResources() const;
    bool isHisTurn() const { return hisTurn; }
    
    std::vector<Vertice *> getPlacesOfPlayer() const { return placesOfPlayer; }
    std::vector<Edge *> getRoads() const { return roads; }
    
    void printPoints() const;
    void printRoads() const;
    void printPlaces() const;
    void printResources() const;

    void setHisTurn(bool hisTurn) { this->hisTurn = hisTurn; }
    bool Has2RoadsBetween(const Vertice *v) const;
    void placeSettelemnt(std::vector<std::string> places, std::vector<int> placesNum, const Board &board);
    void placeRoad(std::vector<std::string> places, std::vector<int> placesNum, const Board &Board);
    void chengeSettlementToCity(std::vector<std::string> places, std::vector<int> placesNum, const Board &board);
    void tradeResours(Player *player, ResourceType give, ResourceType get, int amountget, int amountgive);
    void tradeCard(Player *player, CardType give, CardType get);
    void RemoveOraddResource(ResourceType resource, int count);
    void upDatePoints(int points) { this->points += points; }
    void removeMaxResource();
    void addOrRemoveCard(CardType card, int count);
};

#endif
