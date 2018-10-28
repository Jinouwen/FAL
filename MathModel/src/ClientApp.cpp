#include "ClientApp.h"
ClientApp::ClientApp()
{
    //ctor
}

ClientApp::~ClientApp()
{
    c.send("lgot");
    //dtor
}
std::string ClientApp::expectRec(std::string opt)
{
    std::string cRec;
    while(1)
    {
        while(cRec = c.recieve(),cRec == "");
        std::cerr<<"#server:"+cRec<<"#"<<std::endl;
        if(cRec.substr(0,4) == opt) return cRec.substr(4);
    }
}

int ClientApp::connect()
{
    printf("Connect to Server\n");
    clock_t cStart;
    cStart = clock();
    //211.83.102.34   //192.168.1.101  // port:60000
    //int port;
    //cout<<"port:";
    //cin>>port;
    while (!c.connect("192.168.1.101",60000)){
        if(clock()-cStart>1000)
        {
            printf(".\n");
            cStart=clock();
        }
    }
//    std::cerr<<"233"<<std::endl;cRec[0]
//    std::string name, pwd;
//    std::cin >> name >> pwd;
//    c.log_in(name, pwd);
//    int cnt=0;
//    while (true){
//        cnt++;
//        std::cerr<<cnt<<std::endl;
//        std::string s = c.recieve();
//        if (s != "") {
//            std::cout << s << std::endl;
//        }
//    }
    return 1;
}
int ClientApp::logIn()
{
    while(1)
    {
        std::string userName,password;
        std::cerr<<"log in or sign up:"<<std::endl;
        std::cin>>userName>>password;
        c.log_in(userName,password);
        //c.log_in("jow","666");
        std::string cRec = expectRec("lgin");
        if(cRec == "done") return 0;
        if(cRec == "ntfd")
        {
            while(1)
            {
                printf("sign up ...\n");
                c.sign_up(userName,password);
                cRec = expectRec("siup");
                if(cRec == "done")
                {
                    printf("Sign up success!\n Now you can log in\n");
                    break;
                }
                else
                {
                    printf("Sorry can not sign up,check your user name or password\n");
                    break;
                }
            }
        }
    }
}
int ClientApp::startGame()
{
    printf("press any key to start a new game\n");
    system("pause");

    c.send("prep");
    printf("searching for other players,please wait\n");

    std::string cRec;
    cRec = expectRec("prep");
    cmm.init(cRec[0]-'0',cRec.substr(1));
    printf("game start!\n");
    cRec = expectRec("card");
    cmm.myself.addCard(Player::stringToCardSet(cRec));
    cRec = expectRec("csld");
    int now = cRec[0]-'0';
    int lastId = -1,firstId = -1;
    char ch;
    for(int i=1;i<=3;++i)
    {
        cmm.ClientShowSituation();
        if(now == cmm.myId)
        {
            printf("\n\nDo you want to be the landlord?\n1:Yes       0:No\n");
            while(ch=getchar(),ch!='0'&&ch!='1');
            c.send("beld"+Player::to_string(ch-'0'));
        }
        else
        {
            printf("\n\nwait for [");
            cout<<cmm.playerName[now]<<"]"<<endl;;
        }
        cRec = expectRec("beld");
        if(cRec[0] == '1')
        {
            if(lastId == -1 ) firstId =now;
            lastId = now;
            cmm.bldFlag[now] = 2;
            cmm.scoreRate = cmm.scoreRate == 0 ? 1 : cmm.scoreRate*2;
        }
        else
        {
            cmm.bldFlag[now] = 1;
        }
        now++;
        now%=3;
    }
    if(lastId != -1 && lastId !=firstId)
    {
        now = firstId;
        if(now == cmm.myId)
        {
            printf("\n\nDo you want to be the landlord?\n1:Yes       0:No\n");
            while(ch=getchar(),ch!='0'&&ch!='1');
            c.send("beld"+Player::to_string(ch-'0'));
        }
        else
        {
            printf("\n\nwait for [");
            cout<<cmm.playerName[now]<<"]"<<endl;;
        }
        cRec = expectRec("beld");
        if(cRec[0] == 1)
        {
            cmm.scoreRate = cmm.scoreRate == 0 ? 1 : cmm.scoreRate*2;
            lastId = now;
        }
    }
    for(int i=0;i<3;++i) cmm.bldFlag[i] = 0;

    if(lastId == -1)
    {
        printf("No one wanna be the landlord \nGame Over\n\n\n\n");
        return 1;
    }

    if(lastId == cmm.myId)
    {
        c.send("ldld");
        cRec = expectRec("card");
        cardSet temp;
        cmm.hiddenCards.addCard(temp = Player::stringToCardSet(cRec));
        cmm.myself.addCard(temp);
    }
    else
    {
        cRec = expectRec("card");
        cmm.hiddenCards.addCard(Player::stringToCardSet(cRec));
    }

    cmm.ldId = lastId;
    cmm.bldFlag[cmm.ldId] = 3;
    cmm.cardNum[cmm.ldId]+=3;

    now=cmm.ldId;
    int last = -1;
    while(1)
    {

        cmm.passFlag[now] = 0;
        if(now == last) cmm.table.clear();
        cmm.ClientShowSituation();
        if(now == cmm.myId)
        {
            printf("Its your turn:\n");
            cardSet temp;
            while(temp = cmm.myself.choseCard(),
                  !MathModel::checkFollow(cmm.table,temp))
            {
                cout<<Player::getCardType(temp)<<" can not follow "<<Player::getCardType(cmm.table);

            }
            cmm.myself.eraseCard(temp);
            std::string toSend = Player::CardSetToString(temp);
            std::cerr<<"send"+toSend<<std::endl;
            c.use_card(toSend);
        }
        else
        {
            cout<<"Its "<<cmm.playerName[now]<<"'s turn,please wait"<<endl;
        }
        cRec = expectRec("uscd");
        cardSet temp = Player::stringToCardSet(cRec);
        if(temp.size() == 0)
        {
            cmm.passFlag[now]=1;
        }
        else
        {
            last = now;
            cmm.passFlag[now]=0;
            cmm.table = temp;
            cmm.cardNum[now] -= temp.size();
            if(cmm.cardNum[now] == 0)
            {
                if(now == cmm.myId)
                {
                    printf("\n\n----------------------------------\nCongratulation!!! You are the winner!!!\n----------------------------------\n");
                    c.send("wins");
                }
                else
                {
                    printf("\n\n----------------------------------\nThe winner is [%s]\n----------------------------------\n",cmm.playerName[now].c_str());
                }
                break;
            }
        }
        now = (now+1) % 3;

    }
    system("pause");
    return 1;
}
void ClientApp::test()
{
    std::cerr<<"test Start"<<std::endl;


    logIn();
    while(1)
    {
        startGame();
    }



    std::cerr<<"test Done"<<std::endl;
}
