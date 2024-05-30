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
    //Vertice *findCommonVertexInBoard(std::vector<Vertice *> vertices1, std::vector<Vertice *> vertices2, std::vector<Vertice *> vertices3, std::vector<Vertice *> allVertices);
    std::map<ResourceType, int> resources;
    int points = 0;

public:
    Player(std::string name) : name(name){};
    // void addVertice(Vertice *v) { this->places.push_back(v); };
    bool Has2RoadsBetween(Vertice *v);
    void placeSettelemnt(std::vector<std::string> places, std::vector<int> placesNum, Board &board);
    void placeRoad(std::vector<std::string> places, std::vector<int> placesNum, Board Board);
    void rollDice();
    void endTurn();
    void printPoints();
    void trade(Player player, std::string give, std::string get, int amountget, int amountgive);
    void RemoveOraddResource(ResourceType resource, int count);
    std::string getName() { return name; }
    int getPoints() { return points; }
    std::vector<Vertice *> getPlacesOfPlayer() { return placesOfPlayer; } 
    std::vector<Edge *> getRoads() { return roads; }
    void printRoads() const;
    void printResources()const;
};

#endif