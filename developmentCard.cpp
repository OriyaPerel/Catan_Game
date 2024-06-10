#include "developmentCard.hpp"


void developmentCard::startActive(Player *player)
{
    if (this->isBought == false)
    {
        throw std::invalid_argument("The card is not Bought");
    }
    if (player->isHisTurn() == false)
    {
        throw std::invalid_argument("It's not your turn so you can't use the card");
    }
}
void developmentCard::endActive(Player *player)
{
    player->RemoveOraddResource(ResourceType::ore, -1);
    player->RemoveOraddResource(ResourceType::grain, -1);
    player->RemoveOraddResource(ResourceType::wool, -1);
    
}

developmentCard::~developmentCard()
{
}
Monopoly::Monopoly(std::vector<Player *> players)
{
    this->players = players;
}

void Monopoly::setResource(ResourceType resource)
{
    this->resource = resource;
}

Monopoly::~Monopoly() {}
void Monopoly::active(Player *player)
{
    if (resource == ResourceType::None)
    {
        throw std::invalid_argument("You need to choose a resource");
    }
    startActive(player);

    for (Player *p : players)
    {
        if (p != player)
        {
            player->RemoveOraddResource(resource, p->getAmountOfResource(resource));
            p->RemoveOraddResource(resource, -p->getAmountOfResource(resource));
        }
    }
    player->addOrRemoveCard(CardType::Monopoly, -1);
    std::cout << "monopoly card is used" << std::endl;

    endActive(player);
}

VictoryPoint::~VictoryPoint() {}
void VictoryPoint::active(Player *player)
{
    startActive(player);
    player->upDatePoints(1);
    std::cout << "now player have: " << player->getPoints() << std::endl;
    std::cout << "VictoryPoint card is used" << std::endl;
    player->addOrRemoveCard(CardType::VictoryPoint, -1);
    endActive(player);
}

RoadBuilding::~RoadBuilding() {}
void RoadBuilding::active(Player *player)
{
    startActive(player);
    player->RemoveOraddResource(ResourceType::brick, 1);
    player->RemoveOraddResource(ResourceType::lumber, 1);
    player->addOrRemoveCard(CardType::RoadBuilding, -1);
    std::cout << "RoadBuilding card is used" << std::endl;

    endActive(player);
}
void YearOfPlenty::setResources(ResourceType resource1, ResourceType resource2)
{
    this->resource1 = resource1;
    this->resource2 = resource2;
}
YearOfPlenty::~YearOfPlenty() {}
void YearOfPlenty::active(Player *player)
{
    if (resource1 == ResourceType::None || resource2 == ResourceType::None)
    {
        throw std::invalid_argument("You need to choose 2 resources");
    }
    startActive(player);
    player->RemoveOraddResource(resource1, 1);
    player->RemoveOraddResource(resource2, 1);
    std::cout << "YearOfPlenty card is used" << std::endl;
    player->addOrRemoveCard(CardType::YearOfPlenty, -1);
    endActive(player);
}

Knight::~Knight() {}
void Knight::active(Player *player)
{
    startActive(player);

    if (player->getCardMap()[CardType::Knight] == 3)
    {
        player->upDatePoints(2);
    }
    std::cout << "Knight card is used" << std::endl;

    endActive(player);
}
