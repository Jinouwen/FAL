
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
        void dealtCards(int randSeed=0);
        void display();
        static bool checkFollow(const cardSet &pre,const cardSet &now);

        void startLocalGame();
        void showSituation(int id);
    protected:

    private:
        int landlordId;
        Player players[3];
        Player hiddenCards;
        static int getRank(const cardSet &x);

        unsigned int rSeed;

};

#endif // MATHMODEL_H
