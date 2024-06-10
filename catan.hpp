#include <vector>
#include "Player.hpp"
#include "Board.hpp"
#include "developmentCard.hpp"
#include <typeinfo>

class Catan
{
private:
  std::vector<Player *> players;
  Board board;
  std::vector<developmentCard *> deck;

public:
  Catan(Player *p1, Player *p2, Player *p3);
  ~Catan() ;
  void ChooseStartingPlayer();
  void initialDeck();
  std::vector<Player *> getPlayers() const { return players; }
  Board &getBoard();
  std::string getCardType(developmentCard *card) const;
  developmentCard *getCard2(CardType card, Player *p);
  void printWinner() const;
  void rollDice(Player *p);
  void rollDice(Player *p, int num);
  void endTurn(Player *p);
  void removeHalfResourefromPleyer();
  std::string cardTypeToString(CardType cardType) const;
  void printPlayerInfo(Player *player) const;
};
