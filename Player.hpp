#ifndef PLAYER_HPP
#define PLAYER_HPP

// #include "Vertice.hpp"
// #include "Hexigon.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <map>
// #include "Board.hpp"

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
    int points = 0;
    int Knights = 0;
    bool hisTurn = false;

public:
    Player() = default;
    Player(std::string name) : name(name){};
    ~Player();
    bool isHisTurn() const { return hisTurn; }
    void setHisTurn(bool hisTurn) { this->hisTurn = hisTurn; }
    bool Has2RoadsBetween(Vertice *v);
    void placeSettelemnt(std::vector<std::string> places, std::vector<int> placesNum, Board &board);
    void placeRoad(std::vector<std::string> places, std::vector<int> placesNum, Board Board);
    void printPoints() const;
    void chengeSettlementToCity(std::vector<std::string> places, std::vector<int> placesNum, Board &board);
    void trade(Player *player, ResourceType give, ResourceType get, int amountget, int amountgive);
    void RemoveOraddResource(ResourceType resource, int count);
    std::string getName() const { return name; }
    int getPoints() const { return points; }
    void upDatePoints(int points) { this->points += points; }
    std::vector<Vertice *> getPlacesOfPlayer() const { return placesOfPlayer; }
    std::vector<Edge *> getRoads() const { return roads; }
    void printRoads() const;
    void printPlaces() const;
    void printResources() const;
    int getAmountOfResource(ResourceType resource) const;
    int getKnights() const { return Knights; }
    void addKnight() { Knights++; }
    int getAmountOfResources() const;
    void removeMaxResource();
};

#endif
