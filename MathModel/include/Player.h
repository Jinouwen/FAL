#ifndef PLAYER_H
#define PLAYER_H

#include <Card.h>
#include <set>
class Player
{
    public:
        Player();
        virtual ~Player();

        bool addCard(unsigned int id);
        bool eraseCard(unsigned int id);

        void showAllCard();
        void clearCards();

    protected:

    private:
        unsigned int index;
        unsigned int reCardsNum;
        std::set<Card> cards;

};

#endif // PLAYER_H
