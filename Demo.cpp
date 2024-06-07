/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Hexigon.hpp"
using namespace std;

int main()
{
    Player *p1 = new Player("Player 1");
    Player *p2 = new Player("Player 2");
    Player *p3 = new Player("Player 3");

    Catan catan(p1, p2, p3);
    // Starting of the game. Every player places two settlements and two roads.
    catan.ChooseStartingPlayer();    // should print the name of the starting player, assume it is Amit.
    Board &board = catan.getBoard(); // get the board of the game.
    board.printBoard();

    //**********Player 1 places two roads and settelemnt**********
    vector<string> places1 = {"ore", "wool", "brick"};
    vector<int> placesNum1 = {10, 2, 6};
    p1->placeSettelemnt(places1, placesNum1, board);
    vector<string> roads1 = {"ore", "wool"};
    vector<int> roadsnum1 = {10, 2};
    p1->placeRoad(roads1, roadsnum1, board);
    vector<string> places2 = {"wool", "lumber", "wool"};
    vector<int> placesNum2 = {2, 9, 4};
    p1->placeSettelemnt(places2, placesNum2, board);
    vector<string> roads2 = {"wool", "lumber"};
    vector<int> roadsNum2 = {2, 9};
    p1->placeRoad(roads2, roadsNum2, board);

    p1->printPlaces();
    p1->printRoads();
    catan.endTurn(p1);

    //**********Player 2 places two roads and settelemnt**********
    vector<string> places3 = {"sea", "sea", "grain"};
    vector<int> placesNum3 = {3, 2, 12};
    p2->placeSettelemnt(places3, placesNum3, board);
    vector<string> roads3 = {"grain", "sea"};
    vector<int> roadsNum3 = {12, 2};
    p2->placeRoad(roads3, roadsNum3, board);
    try // p3 tries to place a settlement in the same location as p2.
    {
        p3->placeSettelemnt(places3, placesNum3, board);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    vector<string> places4 = {"grain", "grain", "lumber"};
    vector<int> placesNum4 = {12, 9, 11};
    p2->placeSettelemnt(places4, placesNum4, board);
    vector<string> roads4 = {"grain", "grain"};
    vector<int> roadsNum4 = {12, 9};
    p2->placeRoad(roads4, roadsNum4, board);

    p2->printPlaces();
    p2->printRoads();
    catan.endTurn(p2);

    //**********Player 3 places two roads and settelemnt**********
    vector<string> places5 = {"lumber", "ore", "lumber"};
    vector<int> placesNum5 = {8, 3, 11};
    p3->placeSettelemnt(places5, placesNum5, board);
    vector<string> roads5 = {"ore", "lumber"};
    vector<int> roadsNum5 = {3, 11};
    p3->placeRoad(roads5, roadsNum5, board);
    vector<string> places6 = {"sea", "sea", "lumber"};
    vector<int> placesNum6 = {5, 6, 8};
    p3->placeSettelemnt(places6, placesNum6, board);
    vector<string> roads6 = {"sea", "lumber"};
    vector<int> roadsNum6 = {5, 8};
    p3->placeRoad(roads6, roadsNum6, board);

    p3->printPlaces();
    p3->printRoads();
    catan.endTurn(p3);

    p3->RemoveOraddResource(ResourceType::lumber, 5);
    p3->RemoveOraddResource(ResourceType::brick, 5);

    //************ the game starts ************
    std::cout << "The game starts" << std::endl;
    catan.rollDice(p1, 8); // p1 rolls the dice and gets 8

    p1->RemoveOraddResource(ResourceType::ore, 6);
    p1->RemoveOraddResource(ResourceType::grain, 8);
    p1->RemoveOraddResource(ResourceType::wool, 6);

    Monopoly *monopolyCard = dynamic_cast<Monopoly *>(catan.getCard(CardType::Monopoly));
    monopolyCard->setResource(ResourceType::wool);
    monopolyCard->active(p1);
    p1->trade(p3, ResourceType::grain, ResourceType::lumber, 1, 2);
    p1->trade(p3, ResourceType::ore, ResourceType::brick, 1, 2);
    p1->chengeSettlementToCity(places1, placesNum1, board);


    catan.endTurn(p1);

    p2->RemoveOraddResource(ResourceType::ore, 6);
    p2->RemoveOraddResource(ResourceType::grain, 6);
    p2->RemoveOraddResource(ResourceType::wool, 6);

    Knight *knightCard = dynamic_cast<Knight *>(catan.getCard(CardType::Knight));
    knightCard->active(p2);

    p2->trade(p3, ResourceType::ore, ResourceType::lumber, 1, 1);
    p2->trade(p3, ResourceType::wool, ResourceType::lumber, 1, 2);

    catan.endTurn(p2);

    p3->RemoveOraddResource(ResourceType::lumber, 5);
    p3->RemoveOraddResource(ResourceType::brick, 5);

    vector<string> roads7 = {"grain", "lumber"};
    vector<int> roadsNum7 = {9, 8};
    p3->placeRoad(roads7, roadsNum7, board);

    vector<string> roads8 = {"None", "lumber"};
    vector<int> roadsNum8 = {0, 11};
    p3->placeRoad(roads8, roadsNum8, board);
    // vector<string> roads9 = {"brick", "lumber"};
    // vector<int> roadsNum9 = {6, 11};
    // p3->printResources();
    // p3->placeRoad(roads9, roadsNum9, board);
    // p3->printResources();
    YearOfPlenty *yearOfPlentyCard = dynamic_cast<YearOfPlenty *>(catan.getCard(CardType::YearOfPlenty));
    yearOfPlentyCard->setResources(ResourceType::brick, ResourceType::lumber);
    yearOfPlentyCard->active(p3);

    catan.endTurn(p3);

    // knightCard->active(p2); // Should throw an exception because the card is already used.
    // catan.printPlayerInfo(p2);

    catan.rollDice(p1, 7); // p1 rolls the dice and gets 7
    p1->printResources();
    //  Knight *knightCard2 = dynamic_cast<Knight *>(catan.getCard(CardType::Knight));
    //  knightCard2->active(p1); //should throw an exception because p1 dont have enough resources to buy the card.
 
 //************ the round end ************
    catan.printPlayerInfo(p1);
    catan.printPlayerInfo(p2);
    catan.printPlayerInfo(p3);
    catan.printWinner(); // Should print None because no player reached 10 points.
}
