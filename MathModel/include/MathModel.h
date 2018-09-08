#ifndef MATHMODEL_H
#define MATHMODEL_H
#include <Player.h>

class MathModel
{
    public:
        MathModel();
        virtual ~MathModel();
        void dealtCards();
        void display();
    protected:

    private:
        Player players[3];
        Player hiddenCards;

};

#endif // MATHMODEL_H
