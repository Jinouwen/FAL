#ifndef PLAYER_H
#define PLAYER_H

#include <Card.h>
#include <set>
#include <cstring>
#include <sstream>
typedef  std::set<Card> cardSet;
class Player
{
    public:
        Player();
        virtual ~Player();

        bool addCard(unsigned int id);
        bool addCard(cardSet x);
        bool eraseCard(unsigned int id);
        bool eraseCard(cardSet x);
        void clearCards();
        static std::string getCardType(const cardSet &x);
        static void showAllCard(cardSet &cards,int opt=0);
        static cardSet stringToCardSet(std::string str);
        static std::string CardSetToString(const cardSet & cards);
        static std::string to_string(int x);
        int getCardsNum();

        void showAllCard(int opt=0);//1 for show id
        void showType();
        cardSet getCardSet();
        cardSet choseCard();
    protected:

    private:
        unsigned int index;
        unsigned int cardsNum;
        cardSet cards;


};

#endif // PLAYER_H
