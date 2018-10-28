#include "ClientMathModel.h"

ClientMathModel::ClientMathModel()
{
    //ctor
}

ClientMathModel::~ClientMathModel()
{
    //dtor
}

void ClientMathModel::showMyself()
{
    myself.showAllCard();
}
void ClientMathModel::init(int _myId,string str)
{
    myself.clearCards();
    table.clear();
    hiddenCards.clearCards();
    stringstream ss(str);
    ss>>playerName[0]>>playerName[1]>>playerName[2];
    myId = _myId;
    rightId = (myId + 1) % 3;
    leftId = (rightId + 1) % 3;
    ldId = -1;
    scoreRate = 0;
    for(int i=0;i<3;++i)
    {
        cardNum[i] = 17;
        passFlag[i] = 0;
        bldFlag[i] = 0;
    }
}
void ClientMathModel::ClientShowSituation()
{
    for(int i=0;i<3;++i)
    {
        if(bldFlag[i] == 0)
            ldstr[i] = "          ";
        else if(bldFlag[i] == 1)
            ldstr[i] = " give up  ";
        else if(bldFlag[i] == 2)
            ldstr[i] = " I want   ";
        else if(bldFlag[i] == 3)
            ldstr[i] = " Landlord ";

    }
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<"--------------------------------------------------------------------------------------------------------------"<<endl;
    printf("                        landlord's extra cards:\n                          ");
    if(ldId == -1)
        printf("? ? ?\n");
    else
        hiddenCards.showAllCard();
    cout<<"["<<playerName[leftId]<<setw(42)<<setfill(' ')<<left<<"]";
    cout<<"["<<playerName[rightId]<<"]"<<endl;
    cout<<"Remain:"<<setw(38)<<setfill(' ')<<left<<cardNum[leftId];
    cout<<"Remain:"<<cardNum[rightId]<<endl;
    cout<<"  "<<(passFlag[leftId]?"PASS":"   ")<<"                                         "<<(passFlag[rightId]?"PASS":"   ")<<endl;
    cout<<" "<<ldstr[leftId]<<"                                 "<<ldstr[rightId]<<endl;

    cout<<endl<<endl<<endl<<"                     ";

    Player::showAllCard(table);
    cout<<endl<<endl<<endl<<endl;
    cout<<"                    "<<"Scord Rate: X"<<scoreRate<<endl<<endl<<endl;
    cout<<"                       "<<(passFlag[myId]?"PASS":"   ")<<endl;
    cout<<"                     "<<ldstr[myId]<<endl;
    cout<<"                       "<<"["<<playerName[myId]<<"]"<<endl;
    cout<<endl;
    showMyself();
    cout<<endl<<endl<<endl;
    cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
}
