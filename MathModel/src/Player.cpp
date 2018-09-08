#include "Player.h"

Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

bool Player::addCard(unsigned int id)
{
    Card temp(id);
    if(cards.find(temp)!=cards.end()) return 0;
    cards.insert(temp);
    return 1;
}
bool Player::eraseCard(unsigned int id)
{
    Card temp(id);
    if(cards.find(temp)==cards.end()) return 0;
    cards.erase(temp);
    return 1;
}

void Player::showAllCard()
{
    std::set<Card>::iterator iter=cards.begin();
    while(iter!=cards.end())
    {
        (*iter).showInTerminal();
        iter++;
    }

}
void Player::clearCards()
{
    cards.clear();
}
