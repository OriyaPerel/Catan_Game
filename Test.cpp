
#include "doctest.h"
#include "Player.hpp"
#include "Board.hpp"
#include "Hexigon.hpp"
#include "catan.hpp"
#include "developmentCard.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
using namespace std;

Player p1("Player 1");
Player p2("Player 2");
Player p3("Player 3");

Catan game(&p1, &p2, &p3);

Board &board = game.getBoard();

TEST_CASE("the player is created with the correct name")
{
    CHECK(p1.getName() == "Player 1");
}

TEST_CASE("the turn is set and pass correctly")
{
    CHECK(p1.isHisTurn() == true);
    CHECK(p2.isHisTurn() == false);
    game.endTurn(&p1);
    CHECK(p1.isHisTurn() == false);
    CHECK(p2.isHisTurn() == true);
}

TEST_CASE("negative amount of resources")
{
    CHECK_THROWS_WITH(p1.RemoveOraddResource(ResourceType::brick, -1), "Cannot remove more resources than available");
}

TEST_CASE("the player dont have enough resources or its not his turn for settlement")
{

    vector<string> places2 = {"lumber", "ore", "lumber"};
    vector<int> placesNum2 = {8, 3, 11};

    CHECK_THROWS_WITH(p1.placeSettelemnt(places2, placesNum2, board), "It's not your turn");
    vector<string> places3 = {"sea", "sea", "grain"};
    vector<int> placesNum3 = {3, 2, 12};
    p2.placeSettelemnt(places3, placesNum3, board);
    vector<string> places4 = {"grain", "grain", "lumber"};
    vector<int> placesNum4 = {12, 9, 11};
    p2.placeSettelemnt(places4, placesNum4, board);
    p2.RemoveOraddResource(ResourceType::brick, -1);
    CHECK_THROWS_WITH(p2.placeSettelemnt(places2, placesNum2, board), "There are no 2 roads between the vertex and the player's settlements");
}

TEST_CASE("the player can place a settelemt in corrent place")
{
    vector<string> places2 = {"grain", "grian", "sea"};
    vector<int> placesNum2 = {9, 12, 3};
    CHECK_THROWS_MESSAGE(p3.placeSettelemnt(places2, placesNum2, board), "There is already a settlement in this edge");
    vector<string> places3 = {"sea", "grian", "sea"};
    vector<int> placesNum3 = {4, 9, 3};
    CHECK_THROWS_MESSAGE(p3.placeSettelemnt(places3, placesNum3, board), "There are no 2 roads between the vertex and the player's settlements");
}

TEST_CASE("the player can place a road in corrent place")
{
    vector<string> roads3 = {"sea", "lumber"};
    vector<int> roadsNum3 = {4, 11};
    CHECK_THROWS_MESSAGE(p2.placeRoad(roads3, roadsNum3, board), "There is no common edge in this places");

    vector<string> roads4 = {"wool", "lumber"};
    vector<int> roadsNum4 = {2, 9};
    CHECK_THROWS_MESSAGE(p2.placeRoad(roads4, roadsNum4, board), "There is no settlement in this edge");

    CHECK_THROWS_MESSAGE(p2.placeRoad(roads4, roadsNum4, board), "There is already a road in this edge");

    vector<string> roads5 = {"grain", "grain"};
    vector<int> roadsNum5 = {12, 9};
    p2.placeRoad(roads5, roadsNum5, board);
    CHECK(p2.getRoads()[0]->toString() == "roade:17-> 16"); // check if the road is placed in the correct place

    vector<string> roads6 = {"grain", "sea"};
    vector<int> roadsNum6 = {12, 2};
    p2.placeRoad(roads6, roadsNum6, board);
    CHECK(p2.getRoads()[1]->toString() == "roade:7-> 14"); // check if the road is placed in the correct place

    vector<string> roads7 = {"ore", "sea"};
    vector<int> roadsNum7 = {10, 1};

    CHECK_THROWS_MESSAGE(p2.placeRoad(roads7, roadsNum7, board), "There is not a path to this edge");
    game.endTurn(&p2);
}

TEST_CASE("chenging settlement to city")
{
    vector<string> places1 = {"sea", "sea", "lumber"};
    vector<int> placesNum1 = {5, 6, 8};
    p3.placeSettelemnt(places1, placesNum1, board);

    CHECK_THROWS_WITH(p1.chengeSettlementToCity(places1, placesNum1, board), "It's not your turn");

    CHECK_THROWS_WITH(p3.chengeSettlementToCity(places1, placesNum1, board), "player can't buy a city");

    // Now give p3 enough resources, but ensure they don't own the settlement
    p3.RemoveOraddResource(ResourceType::ore, 3);
    p3.RemoveOraddResource(ResourceType::grain, 2);
    CHECK(p3.getPlacesOfPlayer()[0]->getPieceType() == "settlement");

    p3.chengeSettlementToCity(places1, placesNum1, board); // change the settlement to city
    CHECK(p3.getPlacesOfPlayer()[0]->getPieceType() == "City");
    game.endTurn(&p3);
    p1.RemoveOraddResource(ResourceType::ore, 3);
    p1.RemoveOraddResource(ResourceType::grain, 2);

    CHECK_THROWS_WITH(p1.chengeSettlementToCity(places1, placesNum1, board), "You can't chenge this settlment, it's not yours");
}

TEST_CASE("trade resours")
{
    CHECK_THROWS_WITH(p3.tradeResours(&p2, ResourceType::brick, ResourceType::grain, 2, 1), "It's not your turn");
    CHECK_THROWS_WITH(p1.tradeResours(&p1, ResourceType::brick, ResourceType::grain, 2, 1), "You can't trade with yourself");
    CHECK_THROWS_WITH(p1.tradeResours(&p3, ResourceType::brick, ResourceType::grain, 3, 3), "You don't have enough resources to trade");
    p1.printResources();
    p3.printResources();
    CHECK(p1.getAmountOfResource(ResourceType::ore) == 3);
    CHECK(p3.getAmountOfResource(ResourceType::grain) == 1);
    CHECK(p3.getAmountOfResource(ResourceType::ore) == 0);
    CHECK(p1.getAmountOfResource(ResourceType::grain) == 2);
    p1.tradeResours(&p3, ResourceType::ore, ResourceType::grain, 1, 1);
    CHECK(p1.getAmountOfResource(ResourceType::ore) == 2);
    CHECK(p3.getAmountOfResource(ResourceType::grain) == 0);
    CHECK(p3.getAmountOfResource(ResourceType::ore) == 1);
    CHECK(p1.getAmountOfResource(ResourceType::grain) == 3);
    game.endTurn(&p1);
    game.endTurn(&p2);
}

TEST_CASE("development card")
{
    CHECK_THROWS_WITH(game.getCard2(CardType::Knight, &p3), "You don't have enough resources");
    p3.RemoveOraddResource(ResourceType::ore, 4);
    p3.RemoveOraddResource(ResourceType::grain, 4);
    p3.RemoveOraddResource(ResourceType::wool, 4);
    CHECK_THROWS_WITH(game.getCard2(CardType::Knight, &p2), "It's not your turn so you can't get a card");
}
TEST_CASE("Knight card")
{
    CHECK(p3.getCardMap()[CardType::Knight] == 0);
    Knight *knightCard1 = dynamic_cast<Knight *>(game.getCard2(CardType::Knight, &p3));
    knightCard1->active(&p3);
    CHECK(p3.getCardMap()[CardType::Knight] == 1);

    Knight *knightCard2 = dynamic_cast<Knight *>(game.getCard2(CardType::Knight, &p3));
    knightCard2->active(&p3);

    CHECK(p3.getPoints() == 2);
    Knight *knightCard3 = dynamic_cast<Knight *>(game.getCard2(CardType::Knight, &p3));
    knightCard3->active(&p3);
    CHECK(p3.getPoints() == 4);
    CHECK(p3.getCardMap().at(CardType::Knight) == 3);

    CHECK_THROWS_WITH(game.getCard2(CardType::Knight, &p3), "No card of requested type available"); // there is exacly 3 knight cards in the deck
}

TEST_CASE("Monopoly card")
{
    p3.RemoveOraddResource(ResourceType::ore, 4);
    p3.RemoveOraddResource(ResourceType::grain, 4);

    Monopoly *monopolyCard = dynamic_cast<Monopoly *>(game.getCard2(CardType::Monopoly, &p3));
    CHECK_THROWS_WITH(monopolyCard->active(&p3), "You need to choose a resource");

    monopolyCard->setResource(ResourceType::wool);
    CHECK(p3.getCardMap().at(CardType::Monopoly) == 1);
    CHECK(monopolyCard->isBought == true);
    monopolyCard->active(&p3);
    CHECK(p3.getCardMap().at(CardType::Monopoly) == 0);

    CHECK(p3.getAmountOfResource(ResourceType::wool) == 3);
    CHECK(p1.getAmountOfResource(ResourceType::wool) == 0);
    CHECK(p2.getAmountOfResource(ResourceType::wool) == 0);
}

TEST_CASE("VictoryPoint card")
{
    p3.RemoveOraddResource(ResourceType::ore, 4);
    p3.RemoveOraddResource(ResourceType::grain, 4);
    p3.RemoveOraddResource(ResourceType::wool, 4);

    CHECK(p3.getPoints() == 4);
    VictoryPoint *victoryPointCard = dynamic_cast<VictoryPoint *>(game.getCard2(CardType::VictoryPoint, &p3));
    victoryPointCard->active(&p3);
    CHECK(p3.getPoints() == 5);
}

TEST_CASE("RoadBuilding card")
{
    CHECK(p3.getAmountOfResource(ResourceType::brick) == 1);
    CHECK(p3.getAmountOfResource(ResourceType::lumber) == 1);

    RoadBuilding *roadBuildingCard = dynamic_cast<RoadBuilding *>(game.getCard2(CardType::RoadBuilding, &p3));
    roadBuildingCard->active(&p3);
    CHECK(p3.getAmountOfResource(ResourceType::brick) == 2);
    CHECK(p3.getAmountOfResource(ResourceType::lumber) == 2);
}

TEST_CASE("YearOfPlenty card")
{
    CHECK(p3.getAmountOfResource(ResourceType::brick) == 2);
    CHECK(p3.getAmountOfResource(ResourceType::lumber) == 2);
    p3.printResources();

    YearOfPlenty *yearOfPlentyCard = dynamic_cast<YearOfPlenty *>(game.getCard2(CardType::YearOfPlenty, &p3));

    CHECK(yearOfPlentyCard->getIsBought() == true);

    CHECK_THROWS_WITH(yearOfPlentyCard->active(&p3), "You need to choose 2 resources");
    yearOfPlentyCard->setResources(ResourceType::brick, ResourceType::lumber);
    CHECK(p3.getCardMap().at(CardType::YearOfPlenty) == 1);
    yearOfPlentyCard->active(&p3);
    CHECK(p3.getCardMap().at(CardType::YearOfPlenty) == 0);

    CHECK(p3.getAmountOfResource(ResourceType::brick) == 3);
    CHECK(p3.getAmountOfResource(ResourceType::lumber) == 3);
}

TEST_CASE("trade develomentcard")
{
    game.endTurn(&p3);

    p1.RemoveOraddResource(ResourceType::wool, 2);
    YearOfPlenty *yearOfPlentyCard1 = dynamic_cast<YearOfPlenty *>(game.getCard2(CardType::YearOfPlenty, &p1));
    CHECK(p1.getCardMap().at(CardType::YearOfPlenty) == 1);
    CHECK(p3.getCardMap().at(CardType::Knight) == 3);

    p1.tradeCard(&p3, CardType::YearOfPlenty, CardType::Knight);
    CHECK(p1.getCardMap().at(CardType::YearOfPlenty) == 0);
    CHECK(p3.getCardMap().at(CardType::Knight) == 2);
}

TEST_CASE("roll 7")
{
    CHECK(p3.getAmountOfResources() == 21);
    game.rollDice(&p1, 7);
    CHECK(p3.getAmountOfResources() == 11);
}
