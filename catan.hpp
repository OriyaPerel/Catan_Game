#include <vector>
#include "Player.hpp"
#include "Board.hpp"
#include "developmentCard.hpp"
#include <typeinfo>
enum class CardType
{
    Knight,
    Monopoly,
    YearOfPlenty,
    VictoryPoint,
    RoadBuilding
};

class Catan
{
private:
    std::vector<Player *> players;
    Board board;
    std::vector<developmentCard *> deck;
   

public:
    Catan(Player *p1, Player *p2, Player *p3);
   // ~Catan();
    void ChooseStartingPlayer();
    std::vector<Player *> getPlayers() { return players; }
    Board &getBoard();
    void printWinner()const;
    void rollDice(Player *p);
    void rollDice(Player *p, int num);
    void endTurn(Player *p);
    void removeHalfResourefromPleyer();
    void initialDeck();
    developmentCard *getCard(CardType card);
    std::string cardTypeToString(CardType cardType);
    void printPlayerInfo(Player* player);
    std::string getCardType(developmentCard *card);

    void getCardToPlayer(CardType cardType,Player* player);

};
