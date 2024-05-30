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
// using namespace ariel;

int main()
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("luli");
    Catan catan(p1, p2, p3);
    // Starting of the game. Every player places two settlements and two roads.
    catan.ChooseStartingPlayer();    // should print the name of the starting player, assume it is Amit.
    Board &board = catan.getBoard(); // get the board of the game.
    board.printBoard();
    vector<string> places1 = {"ore", "wool", "brick"};
    vector<int> placesNum1 = {10, 2, 6};
    vector<string> roads1 = {"ore", "wool"};
    vector<int> roadsnum1 = {10, 2};
    p1.placeSettelemnt(places1, placesNum1, board);
    std::cout << p1.getPlacesOfPlayer()[0]->toString() << std::endl;
    p1.placeRoad(roads1, roadsnum1, board);

    vector<string> places2 = {"wool", "lumber", "wool"};
    vector<int> placesNum2 = {2, 9, 4};
    p1.placeSettelemnt(places2, placesNum2, board);
    std::cout << p1.getPlacesOfPlayer()[1]->toString() << std::endl;
    vector<string> roads2 = {"wool", "lumber", "wool"};
    vector<int> roadsNum2 = {2, 9, 4};
    p1.placeRoad(roads2, roadsNum2, board); // p1 chooses Forest, hills, Agricultural Land, Desert with numbers 5, 6, 3, 4.
    p1.printRoads();
    vector<string> places3 = {"sea", "sea", "grain"};
    vector<int> placesNum3 = {3, 2, 12};
    p2.placeSettelemnt(places3, placesNum3, board);
    std::cout << p2.getPlacesOfPlayer()[0]->toString() << std::endl;
    vector<string> roads3 = {"grain", "sea"};
    vector<int> roadsNum3 = {12, 2};
    p2.placeRoad(roads3, roadsNum3, board);
    try
    {
        p3.placeSettelemnt(places3, placesNum3, board); // p3 tries to place a settlement in the same location as p2.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    vector<string> places4 = {"grain", "grain", "lumber"};
    vector<int> placesNum4 = {12, 9, 11};
    p2.placeSettelemnt(places4, placesNum4, board);
    std::cout << p2.getPlacesOfPlayer()[1]->toString() << std::endl;
    vector<string> roads4 = {"grain", "grain"};
    vector<int> roadsNum4 = {12, 9};
    p2.placeRoad(roads4, roadsNum4, board); // p2 chooses Mountains, Pasture Land, and Forest with numbers 4, 9, 5.
    std::cout << "bdikaaaaaaaa" << std::endl;
    p2.printRoads();
    vector<string> places5 = {"lumber", "ore", "lumber"};
    vector<int> placesNum5 = {8, 3, 11};
    // std::cout<<board.printVertice(17)<<std::endl;
    p3.placeSettelemnt(places5, placesNum5, board);
    std::cout << p3.getPlacesOfPlayer()[0]->toString() << std::endl;
    vector<string> roads5 = {"ore", "lumber"};
    vector<int> roadsNum5 = {3, 11};
    p3.placeRoad(roads5, roadsNum5, board);
    vector<string> places6 = {"sea", "sea", "lumber"};
    vector<int> placesNum6 = {5, 6, 8};
    p3.placeSettelemnt(places6, placesNum6, board);
    std::cout << p3.getPlacesOfPlayer()[1]->toString() << std::endl;
    vector<string> roads6 = {"sea", "lumber"};
    vector<int> roadsNum6 = {5, 8};
    p3.placeRoad(roads6, roadsNum6, board);
    vector<string> roads7 = {"grain", "lumber"};
    vector<int> roadsNum7 = {9, 8};
    p3.placeRoad(roads7, roadsNum7, board); // p3 chooses Mountains, Pasture Land, Agricultural Land, Pasture Land with numbers 3, 8, 3, 9.
    p3.printRoads();
    vector<string> roads8 = {"None", "lumber"};
    vector<int> roadsNum8 = {0, 11};
    p3.placeRoad(roads8, roadsNum8, board);
    vector<string> roads9 = {"brick", "lumber"};
    vector<int> roadsNum9 = {6, 11};
    p3.printResources();
    p3.placeRoad(roads9, roadsNum9, board);
    p3.printResources();

    // p1 has wood,bricks, and wheat, p2 has wood, ore, and wool, p3 has ore, wool, wheat.
    //     p1.rollDice();                                    // Lets say it's print 4. Then, p2 gets ore from the mountations.
    //     p1.placeRoad({"Forest", "Hills"}, {5, 6}, board); // p1 continues to build a road.
    //     p1.endTurn();                                     // p1 ends his turn.

    //     p2.rollDice(); // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    //     p2.endTurn();  // p2 ends his turn.

    //     p3.rollDice(); // Lets say it's print 3. Then, p3 gets wheat from the Agricultural Land and Ore from the Mountains, p1 gets wheat from the Agricultural Land.
    //     p3.endTurn();  // p3 ends his turn.

    //     try
    //     {
    //         p2.rollDice(); // p2 tries to roll the dice again, but it's not his turn.
    //     }
    //     catch (const std::exception &e)
    //     {
    //         cout << e.what() << endl;
    //     }

    //     p1.rollDice();                       // Lets say it's print 6. Then, p1 gets bricks from the hills.
    //     p1.trade(p2, "wood", "brick", 1, 1); // p1 trades 1 wood for 1 brick with p2.
    //     p1.endTurn();                        // p1 ends his turn.

    //     p2.rollDice(); // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    //                    // p2.buyDevelopmentCard(); // p2 buys a development card. Lets say it is a bonus points card.
    //     p2.endTurn();  // p2 ends his turn.

    //     p1.printPoints(); // p1 has 2 points because it has two settelments.
    //     p2.printPoints(); // p2 has 3 points because it has two settelments and a bonus points card.
    //     p3.printPoints(); // p3 has 2 points because it has two settelments.

    //     catan.printWinner(); // Should print None because no player reached 10 points.
}