
#ifndef MATHMODEL_H
#define MATHMODEL_H
#include <Player.h>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <algorithm>

class MathModel
{
    public:
        MathModel();
        virtual ~MathModel();
        void dealtCards();
        void display();
        bool checkFollow(const cardSet &pre,const cardSet &now);
    protected:

    private:
        Player players[3];
        Player hiddenCards;

};

#endif // MATHMODEL_H
