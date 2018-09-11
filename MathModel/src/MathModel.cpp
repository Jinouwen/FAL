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
int MathModel::getRank(const cardSet &x)
{
    unsigned int size = x.size();
    int temp[25];
    std::set<Card>::iterator iter=x.begin();
    for(unsigned int i=1;i<=size;++i,++iter)
    {
        temp[i]= (*iter).num;
    }

    if(size==4)
    {
        if(temp[1]!=temp[2]&&temp[2]==temp[3]&&temp[3]==temp[4]) return temp[2];
        if(temp[1]==temp[2]&&temp[2]==temp[3]&&temp[3]!=temp[4]) return temp[1];
    }
    if(size==5)
    {
        if(temp[1]==temp[2]&&temp[2]==temp[3]&&temp[3]!=temp[4]&&temp[4]==temp[5]) return temp[1];
        if(temp[1]==temp[2]&&temp[2]!=temp[3]&&temp[3]==temp[4]&&temp[4]==temp[5]) return temp[3];
    }
    if(size == 6 )
    {
        if(temp[1]==temp[2]&&temp[2]==temp[3]&&temp[3]==temp[4]&&temp[4]!=temp[5]&&temp[5]!=temp[6]) return temp[1];
        if(temp[1]!=temp[2]&&temp[2]!=temp[3]&&temp[3]==temp[4]&&temp[4]==temp[5]&&temp[5]==temp[6]) return temp[3];
        if(temp[1]!=temp[2]&&temp[2]==temp[3]&&temp[3]==temp[4]&&temp[4]==temp[5]&&temp[5]!=temp[6]) return temp[2];
    }
    if(size >=8 && size%4==0)
    {
        int num=size/4;
        unsigned int flag;
        for(unsigned int i=1;i+num*3-1<=size;++i)
        {
            flag=i;
            for(unsigned int j=i+2;j<=i+num*3-1;j+=3)
            {
                if(temp[j]!=temp[j-1]||temp[j-1]!=temp[j-2]) flag=0;
                if(j<i+num*3-1&&temp[j]!=temp[j+1]-1) flag=0;
            }
            if(flag) break;
        }
        if(flag&&temp[flag+num*3-1]<=12)
        {
            for(unsigned int i=2;i<=size;++i)
            {
                if((i<flag||i>flag+num*3-1) && (i-1<flag||i-1>flag+num*3-1)&& temp[i]==temp[i-1]) flag=0;
            }
            if(flag) return temp[flag];
        }
    }
    if(size >=10 && size%5==0)
    {
        int num=size/5;
        unsigned int flag;
        for(unsigned int i=1;i+num*3-1<=size;++i)
        {
            flag=i;
            for(unsigned int j=i+2;j<=i+num*3-1;j+=3)
            {
                if(temp[j]!=temp[j-1]||temp[j-1]!=temp[j-2]) flag=0;
                if(j<i+num*3-1&&temp[j]!=temp[j+1]-1) flag=0;
            }
            if(flag) break;
        }
        if(flag&&temp[flag+num*3-1]<=12)
        {
            for(unsigned int i=2;i<flag;i+=2)
            {
                if(temp[i]!=temp[i-1]) flag=0;
                if(i+1<=size && temp[i]==temp[i+1]) flag=0;
            }
            for(unsigned int i=flag+num*3+1;i<=size;i+=2)
            {
                if(temp[i]!=temp[i-1]) flag=0;
                if(i+1<=size && temp[i]==temp[i+1]) flag=0;
            }
            if(flag) return temp[flag];
        }
    }
    if(size==8)
    {
        if(temp[1]==temp[2]&&temp[2]!=temp[3]&&temp[3]==temp[4]&&temp[4]!=temp[5]&&temp[5]==temp[6]&&temp[6]==temp[7]&&temp[7]==temp[8]) return temp[5];
        if(temp[1]==temp[2]&&temp[2]!=temp[3]&&temp[3]==temp[4]&&temp[4]==temp[5]&&temp[5]==temp[6]&&temp[6]!=temp[7]&&temp[7]==temp[8]) return temp[3];
        if(temp[1]==temp[2]&&temp[2]==temp[3]&&temp[3]==temp[4]&&temp[4]!=temp[5]&&temp[5]==temp[6]&&temp[6]!=temp[7]&&temp[7]==temp[8]) return temp[1];
    }
    return -1;
}
bool MathModel::checkFollow(const cardSet &pre,const cardSet &now)
{
    if(now.empty()) return 0;
    if(pre.empty()) return 1;
    std::string preType=Player::getCardType(pre);
    std::string nowType=Player::getCardType(now);
    if(preType!=nowType)
    {
        if(preType=="superBoom") return 0;
        if(nowType=="boom") return 1;
        if(nowType=="superBoom") return 1;

        return 0;
    }
    else
    {
        if(preType.find("With")>0)
        {
            return getRank(now)>getRank(pre);
        }
        else
        {
            return ((*now.begin()).id) > ((*pre.begin()).id);
        }
    }

}
unsigned int Card::makeId(int suit,int type)
{
    if(type==14) return 53;
    else if(type==15) return 54;

    return (type-1)*4+suit;
}
