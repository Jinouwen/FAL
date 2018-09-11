#include "MathModel.h"
MathModel::MathModel()
{
    //ctor
}

MathModel::~MathModel()
{
    //dtor
}

void MathModel::dealtCards(int randSeed)
{
    srand(randSeed);
    int rank[55];
    for(int i=1;i<=54;++i)
        rank[i]=i;
    rSeed = randSeed==0?time(0):randSeed;
    srand(rSeed);
    unsigned int randSeed2=rand()%5+1;
    for(unsigned int i=1;i<=randSeed2;++i)
    {
        //if(randSeed==0) srand(time(0));
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

    //std::cerr<<nowType;
    //std::cerr<<preType;

    if(preType!=nowType)
    {
        if(preType=="superBoom") return 0;
        if(nowType=="boom") return 1;
        if(nowType=="superBoom") return 1;

        return 0;
    }
    else
    {
        if(preType.find("With")!=std::string::npos)
        {
            return getRank(now)>getRank(pre);
        }
        else
        {
            return ((*now.begin()).id) > ((*pre.begin()).id);
        }
    }

}


void MathModel::showSituation(int id)
{
    if(id>2||id<0)
    {
        for(int i=0;i<3;++i)
        {
            printf((i==landlordId)?"Landlord:":"Farmer:");
            printf("player%d :",i);
            players[i].showAllCard();
        }
    }
    else
    {
        for(int i=0;i<3;++i)
        if(i!=id)
        {
            printf((i==landlordId)?"Landlord:":"Farmer:");
            printf("player%d : %d cards remaining\n",i,players[i].getCardsNum());
        }
        printf((id==landlordId)?"Landlord:":"Farmer:");
        players[id].showAllCard(1);
    }
}

void MathModel::startLocalGame(unsigned int randSeed)
{
    for(int i=0;i<3;++i) players[i].clearCards();

    dealtCards(randSeed);
    printf("random seed:%u\n",rSeed);

    showSituation(3);
    printf("hidden cards:");
    hiddenCards.showAllCard();
    printf("Who is the landlord?[0-2]\n");
    int now;
    scanf("%d",&now);
    landlordId=now;
    players[now].addCard(hiddenCards.getCardSet());


    cardSet table;
    int last=now;
    while(1)
    {
        system("cls");
        printf("random seed:%u\n",rSeed);
        showSituation(now);
        printf("It's your turn player%d:\n",now);
        if(last == now)
        {
            table.clear();
            printf("no follow needs\n");
        }
        else
        {

            printf("you  should follow :\n");

            std::cerr<<Player::getCardType(table)<<" ";

            Player::showAllCard(table);
        }
        int opt=0;
        cardSet temp;
        while(1)
        {
            temp=players[now].choseCard();
            Player::showAllCard(temp);
            if(last != now &&temp.empty())
            {
                printf("player%d pass\n",now);
                opt=1;
                break;
            }
            if(checkFollow(table,temp))
            {
                opt=2;
                break;
            }
            std::cout<<Player::getCardType(temp)<<std::endl;
            printf("can not follow,please try again");
        }
        if(opt==2)
        {
            table=temp;
            players[now].eraseCard(temp);
            if(players[now].getCardsNum()==0)
            {
                printf("Winner is player%d!! the",now);
                printf((now==landlordId)?"Landlord:\n":"Farmer:\n");
                return;
            }
            last = now;
        }
        now++;
        now%=3;
    }

}
