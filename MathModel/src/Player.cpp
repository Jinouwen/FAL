#include "Player.h"

Player::Player()
{
    cardsNum = 0;
    //ctor
}

Player::~Player()
{
    //dtor
}

bool Player::addCard(unsigned int id)
{
    Card temp(id);
    if(cards.find(temp)!=cards.end()) return 0;
    cards.insert(temp);
    cardsNum++;
    return 1;
}
bool Player::eraseCard(unsigned int id)
{
    Card temp(id);
    if(cards.find(temp)==cards.end()) return 0;
    cards.erase(temp);
    cardsNum--;
    return 1;
}

void Player::showAllCard()
{
    if(cards.empty())
    {
        printf("now car\nd");
        return;
    }
    std::set<Card>::iterator iter=cards.end();
    do
    {
        iter--;
        (*iter).showInTerminal();
    }
    while(iter!=cards.begin());

}
void Player::clearCards()
{
    cards.clear();
}
void Player::showType()
{
    std::cout<<getCardType(cards)<<" ";
}
std::string Player::getCardType(const cardSet &x)
{
    if(x.empty()) return "none";
    unsigned int size = x.size();
    int temp[25];
    std::set<Card>::iterator iter=x.begin();
    for(unsigned int i=1;i<=size;++i,++iter)
    {
        temp[i]= (*iter).num;
    }
    if(size==1) return "single";
    else if(size==2)
    {
        if(temp[1]==14 && temp[2]==15) return "superBoom";
        else if(temp[1]==temp[2]) return "double";
    }
    else if(size==3)
    {
        if(temp[1]==temp[2]-1&&temp[2]==temp[3]-1&&temp[3]<=12) return "triple";
    }
    if(size==4)
    {
        if(temp[1]==temp[2]&&temp[2]==temp[3]&&temp[3]==temp[4]) return "boom";
        if(temp[1]!=temp[2]&&temp[2]==temp[3]&&temp[3]==temp[4]) return "tripleWithSingle";
        if(temp[1]==temp[2]&&temp[2]==temp[3]&&temp[3]!=temp[4]) return "tripleWithSingle";
    }
    if(size==5)
    {
        if(temp[1]==temp[2]&&temp[2]==temp[3]&&temp[3]!=temp[4]&&temp[4]==temp[5]) return "tripleWithDouble";
        if(temp[1]==temp[2]&&temp[2]!=temp[3]&&temp[3]==temp[4]&&temp[4]==temp[5]) return "tripleWithDouble";
    }
    if(size>=5)
    {
        bool flag=1;
        for(unsigned int i=2;i<=size;++i)
        {
            if(temp[i]!=temp[i-1]+1) flag=0;
        }
        if(flag&&temp[size]<=12) return "singleStraight";
    }
    if(size>=6 && (size&1)==0)
    {
        bool flag=1;
        for(unsigned int i=2;i<=size;i+=2)
        {
            if(temp[i]!=temp[i-1]) flag=0;
            if(i<size&&temp[i]!=temp[i+1]-1) flag=0;
        }
        if(flag&&temp[size]<=12) return "doubleStraight";
    }
    if(size>=6 && size%3==0)
    {
        bool flag=1;
        for(unsigned int i=3;i<=size;i+=2)
        {
            if(temp[i]!=temp[i-1]||temp[i-1]!=temp[i-2]) flag=0;
            if(i<size&&temp[i]!=temp[i+1]-1) flag=0;
        }
        if(flag&&temp[size]<=12) return "tripleStraight";
    }
    if(size == 6 )
    {
        if(temp[1]==temp[2]&&temp[2]==temp[3]&&temp[3]==temp[4]&&temp[4]!=temp[5]&&temp[5]!=temp[6]) return "boomWithSingle";
        if(temp[1]!=temp[2]&&temp[2]!=temp[3]&&temp[3]==temp[4]&&temp[4]==temp[5]&&temp[5]==temp[6]) return "boomWithSingle";
        if(temp[1]!=temp[2]&&temp[2]==temp[3]&&temp[3]==temp[4]&&temp[4]==temp[5]&&temp[5]!=temp[6]) return "boomWithSingle";
    }
    if(size >=8 && size%4==0)
    {
        int num=size/4;
        unsigned int flag;
        for(unsigned int i=1;i+num*3-1<=size;++i)
        {
            flag=i;
            for(unsigned int j=i+2;j<=i+num*3-1;j+=2)
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
            if(flag) return "tripleStraightWithSingle";
        }
    }
    if(size >=10 && size%5==0)
    {
        int num=size/5;
        unsigned int flag;
        for(unsigned int i=1;i+num*3-1<=size;++i)
        {
            flag=i;
            for(unsigned int j=i+2;j<=i+num*3-1;j+=2)
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
            if(flag) return "tripleStraightWithDouble";
        }
    }
    if(size==8)
    {
        if(temp[1]==temp[2]&&temp[2]!=temp[3]&&temp[3]==temp[4]&&temp[4]!=temp[5]&&temp[5]==temp[6]&&temp[6]==temp[7]&&temp[7]==temp[8]) return "boomWithDouble";
        if(temp[1]==temp[2]&&temp[2]!=temp[3]&&temp[3]==temp[4]&&temp[4]==temp[5]&&temp[5]==temp[6]&&temp[6]!=temp[7]&&temp[7]==temp[8]) return "boomWithDouble";
        if(temp[1]==temp[2]&&temp[2]==temp[3]&&temp[3]==temp[4]&&temp[4]!=temp[5]&&temp[5]==temp[6]&&temp[6]!=temp[7]&&temp[7]==temp[8]) return "boomWithDouble";
    }
    return "notType";


}
