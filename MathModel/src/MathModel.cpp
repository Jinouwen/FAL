#include "MathModel.h"
MathModel::MathModel()
{
    //ctor
}

MathModel::~MathModel()
{
    //dtor
}

void MathModel::dealtCards()
{
    int rank[55];
    for(int i=1;i<=54;++i)
        rank[i]=i;
    srand(time(0));
    unsigned int randSeed2=rand()%5+1;
    for(unsigned int i=1;i<=randSeed2;++i)
    {
        srand(time(0));
        std::random_shuffle(rank+1,rank+54+1);
    }
    for(int i=1,now=0;i<=51;++i,now = now==2?0:now+1)
    {
        players[now].addCard(rank[i]);
    }
    for(int i=52;i<=54;++i) hiddenCards.addCard(rank[i]);

}
void MathModel::display()
{
    for(int i=0;i<=2;++i)
    {
        players[i].showAllCard();
        puts("");
    }
    hiddenCards.showAllCard();
    puts("");
}
bool MathModel::checkFollow(const cardSet &pre,const cardSet &now)
{
    if(now.empty()) return 0;
    if(pre.empty()) return 1;
}
