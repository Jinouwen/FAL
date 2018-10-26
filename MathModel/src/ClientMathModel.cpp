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
    stringstream ss(str);
    ss>>playerName[0]>>playerName[1]>>playerName[2];
    myId = _myId;
    rightId = (myId + 1) % 3;
    leftId = (rightId + 1) % 3;

    for(int i=0;i<3;++i)
    {
        cardNum[i] = 17;
        passFlag[i] = 0;
    }
    cardNum[0] = 20;
}
void ClientMathModel::ClientShowSituation()
{
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<"--------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"["<<playerName[leftId]<<setw(42)<<setfill(' ')<<left<<"]";
    cout<<"["<<playerName[rightId]<<"]"<<endl;
    cout<<"Remain:"<<setw(38)<<setfill(' ')<<left<<cardNum[leftId];
    cout<<"Remain:"<<cardNum[rightId]<<endl;
    cout<<"  "<<(passFlag[leftId]?"PASS":"   ")<<"                                         "<<(passFlag[rightId]?"PASS":"   ")<<endl;
    cout<<endl<<endl<<endl<<"                     ";

    Player::showAllCard(table);
    cout<<endl<<endl<<endl<<endl;
    cout<<"                       "<<(passFlag[myId]?"PASS":"   ")<<endl;
    cout<<"                       "<<"["<<playerName[myId]<<"]"<<endl;
    cout<<endl;
    showMyself();
    cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
}
