#ifndef PLAYER_H
#define PLAYER_H

#include <Card.h>
#include <set>
typedef  std::set<Card> cardSet;
class Player
{
    public:
        Player();
        virtual ~Player();

        bool addCard(unsigned int id);
        bool eraseCard(unsigned int id);
        void clearCards();
        std::string getCardType(const cardSet &x);

        void showAllCard();
        void showType();

    protected:

    private:
        unsigned int index;
        unsigned int cardsNum;
        cardSet cards;

};

#endif // PLAYER_H
