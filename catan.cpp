
#include "catan.hpp"

#include <iostream>
Catan::Catan(Player *p1, Player *p2, Player *p3)
{
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);
    p1->setHisTurn(true); // p1 is the first player start the game
    initialDeck();        // create the deck of the game
}
Catan::~Catan()
{
    for (developmentCard *card : deck)
    {
        delete card;
    }
}
void Catan::initialDeck()
{
    deck.resize(19);
    int index = 0;

    // Add 3 Knights
    for (int i = 0; i < 3; i++)
    {
        deck[index++] = new Knight();
    }

    // Add 4 of each other card type
    for (int i = 0; i < 4; i++)
    {
        deck[index++] = new Monopoly(players);
        deck[index++] = new YearOfPlenty();
        deck[index++] = new VictoryPoint();
        deck[index++] = new RoadBuilding();
    }
}


developmentCard *Catan::getCard2(CardType cardType, Player *p)
{
    if (p->isHisTurn() == false)
    {
        throw std::invalid_argument("It's not your turn so you can't get a card");
    }
    if ((p->getAmountOfResource(ResourceType::ore) < 1) || (p->getAmountOfResource(ResourceType::grain) < 1) || (p->getAmountOfResource(ResourceType::wool) < 1))
    {
        throw std::invalid_argument("You don't have enough resources");
    }

    for (developmentCard *card : deck)
    {
        if (cardTypeToString(cardType) == getCardType(card) && card->getIsBought() == false)
        {
            p->addOrRemoveCard(cardType, 1);
            card->setBought(true);
            return card;
        }
    }
    throw std::invalid_argument("No card of requested type available");
    return nullptr;
}

std::string Catan::getCardType(developmentCard *card) const
{
    if (card == nullptr)
    {
        return "Null card";
    }

    if (dynamic_cast<Knight *>(card) != nullptr)
    {
        return "Knight";
    }
    else if (dynamic_cast<VictoryPoint *>(card) != nullptr)
    {
        return "VictoryPoint";
    }
    else if (dynamic_cast<Monopoly *>(card) != nullptr)
    {
        return "Monopoly";
    }
    else if (dynamic_cast<YearOfPlenty *>(card) != nullptr)
    {
        return "YearOfPlenty";
    }
    else if (dynamic_cast<RoadBuilding *>(card) != nullptr)
    {
        return "RoadBuilding";
    }
    return "Unknown card type";
}

std::string Catan::cardTypeToString(CardType cardType) const
{
    switch (cardType)
    {
    case CardType::RoadBuilding:
        return "RoadBuilding";
    case CardType::Knight:
        return "Knight";
    case CardType::Monopoly:
        return "Monopoly";
    case CardType::VictoryPoint:
        return "VictoryPoint";
    case CardType::YearOfPlenty:
        return "YearOfPlenty";
    default:
        return "Unknown";
    }
}

void Catan::ChooseStartingPlayer()
{
    if (!players.empty())
    {
        std::cout << "The player starting is " << players[0]->getName() << std::endl;
    }
    else
    {
        std::cout << "No players available" << std::endl;
    }
}
Board &Catan::getBoard()
{
    return board;
}

void Catan::rollDice(Player *p)
{
    if (p->isHisTurn() == false)
    {
        throw std::invalid_argument("It's not your turn so you can't roll the dice");
    }
    int diceRoll = rand() % 12 + 1;
    std::cout << p->getName() << " roll " << diceRoll << std::endl;
    if (diceRoll == 7) // if the dice roll 7 the player need to remove half of his resources
    {
        removeHalfResourefromPleyer();
    }
    else
    {
        std::vector<Hexigon *> hexigons = board.gethexigonsboard();
        for (Hexigon *h : hexigons)
        {
            if (h->getNumber() == diceRoll && h->getType() != "sea")
            {
                std::vector<Vertice *> vertices = h->getVertices();
                for (Vertice *v : vertices)
                {

                    if (v->getOwner() != NULL)
                    {
                        if (v->getPieceType() == "settlement")
                        { // if there is a settlement in the vertex the player get 1 resource
                            v->getOwner()->RemoveOraddResource(h->getResourceType(), 1);
                            std::cout << "add 1 " << h->getResourceType() << " to " << v->getOwner()->getName() << std::endl;
                        }
                        else
                        { // if there is a city in the vertex the player get 2 resources
                            v->getOwner()->RemoveOraddResource(h->getResourceType(), 2);
                            std::cout << "add 2 " << h->getResourceType() << " to " << v->getOwner()->getName() << std::endl;
                        }
                    }
                }
            }
        }
    }
}

void Catan::rollDice(Player *p, int num)
{
    if (p->isHisTurn() == false)
    {
        throw std::invalid_argument("It's not your turn so you can't roll the dice");
    }
    std::cout << p->getName() << " roll " << num << std::endl;
    if (num == 7)
    {
        removeHalfResourefromPleyer();
    }
    else
    {
        std::vector<Hexigon *> hexigons = board.gethexigonsboard();
        for (Hexigon *h : hexigons)
        {
            if (h->getNumber() == num && h->getType() != "sea")
            {
                std::vector<Vertice *> vertices = h->getVertices();
                for (Vertice *v : vertices)
                {

                    if (v->getOwner() != NULL)
                    {
                        if (v->getPieceType() == "settlement")
                        { // if there is a settlement in the vertex the player get 1 resource
                            v->getOwner()->RemoveOraddResource(h->getResourceType(), 1);
                            std::cout << "add 1 " << h->getResourceType() << " to " << v->getOwner()->getName() << std::endl;
                        }
                        else
                        { // if there is a city in the vertex the player get 2 resources
                            v->getOwner()->RemoveOraddResource(h->getResourceType(), 2);
                            std::cout << "add 2 " << h->getResourceType() << " to " << v->getOwner()->getName() << std::endl;
                        }
                    }
                }
            }
        }
    }
}
void Catan::removeHalfResourefromPleyer()
// function that remove half of the resources from the player
// this function is called when the dice roll 7
{
    for (Player *p : players)
    {
        if (p->getAmountOfResources() > 7)
        {
            std::cout << p->getName() << " need to remove half of his resources " << p->getAmountOfResources() << std::endl;
            int needToRemove = p->getAmountOfResources() / 2;
            for (int i = 0; i < needToRemove; i++)
            {
                p->removeMaxResource(); // remove the resource that the player have the most
            }
            std::cout << p->getName() << " now have: " << p->getAmountOfResources() << std::endl;
        }
    }
}

void Catan::endTurn(Player *p)
{
    if (p->isHisTurn() == false)
    {
        throw std::invalid_argument("It's not your turn so you can't end it");
    }
    if (p == this->players[0])
    {
        players[0]->setHisTurn(false);
        players[1]->setHisTurn(true);
        std::cout << "now it's turn of " << players[1]->getName() << std::endl;
    }
    if (p == this->players[1])
    {
        players[1]->setHisTurn(false);
        this->players[2]->setHisTurn(true);
        std::cout << "now it's turn of " << players[2]->getName() << std::endl;
    }
    if (p == this->players[2])
    {
        players[2]->setHisTurn(false);
        this->players[0]->setHisTurn(true);
        std::cout << "now it's turn of " << players[0]->getName() << std::endl;
    }
    if (p->getPoints() >= 10)
    {
        std::cout << "The winner is " << p->getName() << std::endl;
    }
}

void Catan::printWinner() const
{
    for (Player *p : players)
    {
        if (p->getPoints() >= 10)
        {
            std::cout << "the winner is:" << p->getName() << std::endl;
        }
    }
    std::cout << "there is no winner yet.." << std::endl;
}

void Catan::printPlayerInfo(Player *player) const
{
    std::cout << "information about player: " << player->getName() << std::endl;
 // std::cout << "Number of Knights: " << player->getKnights() << std::endl;
    std::cout << "Number of Points: " << player->getPoints() << std::endl;

    std::cout << "Resources:" << std::endl;
    player->printResources();

    std::cout << "Settlements:" << std::endl;
    for (Vertice *v : player->getPlacesOfPlayer())
    {
        std::cout << v->toString() << std::endl;
    }

    std::cout << "Roads:" << std::endl;
    for (Edge *e : player->getRoads())
    {
        std::cout << e->toString() << std::endl;
    }
}
