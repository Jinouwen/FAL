
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
        void dealCards(int randSeed=0);
        void display();
        static bool checkFollow(const cardSet &pre,const cardSet &now);

        void startLocalGame(unsigned int randSeed=0);
        void showSituation(int id);

        Player hiddenCards;
    protected:

    private:
        int landlordId;
        Player players[3];
        static int getRank(const cardSet &x);

        unsigned int rSeed;

};

#endif // MATHMODEL_H
