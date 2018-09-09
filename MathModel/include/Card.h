#ifndef CARD_H
#define CARD_H

#include <cstdio>
#include <iostream>
#include <windows.h>



class Card
{
    public:
        Card();
        Card(unsigned int id);
        virtual ~Card();
        unsigned int id;
        unsigned int num;
        unsigned int suit;
        void showInTerminal() const;

        bool operator <(const Card &b) const
        {
            return id<b.id;
        }
        const char DIS[14]={0,'3','4','5','6','7','8','9','X','J','Q','K','A','2'};

    protected:

    private:

};

#endif // CARD_H
