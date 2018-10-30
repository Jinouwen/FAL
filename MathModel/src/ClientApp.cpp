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
        //std::cerr<<"#server:"+cRec<<"#"<<std::endl;
        if(cRec.substr(0,4) == "edgm") return cRec;
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
    while (! (c.connect("192.168.1.101",60000)  || c.connect("211.83.102.34",60000)))
    {
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
void ClientApp::loadWelcome()
{
    printf("Loading...\n 10 %%\n");
    Sleep(700);
    printf("40 %% \n");
    Sleep(900);
    printf("72 %% \n");
    Sleep(600);
    printf("95 %% \n");
    Sleep(300);
}
int ClientApp::logIn()
{
    system("cls");
    while(1)
    {
        std::cout<<"log in or sign up: \n[userName] [password]\n"<<std::endl;
        std::cin>>userName>>password;
        c.log_in(userName,password);
        //c.log_in("jow","666");
        std::string cRec = expectRec("lgin");
        std::cout<<"Server: "+cRec<<endl;
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
    c.send("prep");
    printf("searching for other players,please wait\n");

    std::string cRec;
    if((cRec = expectRec("prep")) == "edgm") return 1;
    cmm.init(cRec[0]-'0',cRec.substr(1));
    printf("game start!\n");
    if((cRec = expectRec("card")) == "edgm") return 1;
    cmm.myself.addCard(Player::stringToCardSet(cRec));
    if((cRec = expectRec("csld")) == "edgm") return 1;
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
        if((cRec = expectRec("beld")) == "edgm") return 1;
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
        cmm.ClientShowSituation();
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
        if((cRec = expectRec("beld")) == "edgm") return 1;
        if(cRec[0] == '1')
        {
            cmm.scoreRate = cmm.scoreRate == 0 ? 1 : cmm.scoreRate*2;
            lastId = now;
        }
    }
    for(int i=0;i<3;++i) cmm.bldFlag[i] = 0;

    if(lastId == -1)
    {
        printf("No one wanna be the landlord \nGame Over\n\n\n\n");
        return 0;
    }

    if(lastId == cmm.myId)
    {
        c.send("ldld");
        if((cRec = expectRec("card")) == "edgm") return 1;
        cardSet temp;
        cmm.hiddenCards.addCard(temp = Player::stringToCardSet(cRec));
        cmm.myself.addCard(temp);
    }
    else
    {
        if((cRec = expectRec("card")) == "edgm") return 1;
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
                cmm.ClientShowSituation();
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


        if((cRec = expectRec("uscd")) == "edgm") return 1;
        cardSet temp = Player::stringToCardSet(cRec);
        if(temp.size() == 0)
        {
            cmm.passFlag[now]=1;
        }
        else
        {
            if(now!=cmm.ldId) cmm.springFlag = 0;
            last = now;
            string CardsType = Player::getCardType(temp);
            if(CardsType == "boom" || CardsType == "superBoom") cmm.scoreRate*=2;
            cmm.passFlag[now]=0;
            cmm.table = temp;
            cmm.cardNum[now] -= temp.size();
            if(cmm.cardNum[now] == 0)
            {
                if(cmm.springFlag)
                    cmm.scoreRate*=2;
                int winFlag;
                if(now == cmm.myId || ( now != cmm.ldId && cmm.myId != cmm.ldId))
                    winFlag = cmm.myId == cmm.ldId ? 2 : 1;
                else
                    winFlag = cmm.myId == cmm.ldId ? -2 : -1;

                c.send("scor"+Player::to_string(winFlag * cmm.scoreRate));
                c.send("lscd"+Player::CardSetToString(cmm.myself.getCardSet()));
                for(int i=0;i<3;++i)
                {
                    cmm.players[i].clearCards();
                    if((cRec = expectRec("lscd")) == "edgm") return 1;
                    cmm.players[i].addCard(Player::stringToCardSet(cRec));
                }
                cmm.ClientShowSituation(1);
                if(cmm.springFlag)
                    printf("Spring!!\n");
                printf("Final Score rate:%d\n",cmm.scoreRate);
                if(now == cmm.myId) c.send("wins");
                if(winFlag > 0)
                    printf("--------------------------------------\nCongratulation!!! You are the winner!!!\n--------------------------------------\n");
                else
                    printf("----------------------------------\nThe winner is [%s]\n----------------------------------\n",cmm.playerName[now].c_str());
                printf("\nYour score:%d --> %d (%c%d)\n",cmm.playerScore[cmm.myId],cmm.playerScore[cmm.myId]+winFlag * cmm.scoreRate,winFlag>0?'+':'-',abs(winFlag) * cmm.scoreRate);
                break;
            }
        }
        now = (now+1) % 3;

    }
    printf("[1]Continue  [2]Exit to main menu");
    while(ch=getchar(),ch<'0'||ch>'9');
    if(ch == '1') return 2;
    else if(ch == '2') return 0;
    return 0;
}
void ClientApp::test()
{
    std::cerr<<"test Start"<<std::endl;
    //loadWelcome();
    //welcome();
    logIn();
    mainMenu();


    std::cerr<<"test Done"<<std::endl;
}
int ClientApp::mainMenu()
{
    while(1)
    {
        system("cls");
        printf("Welcome [%s],chose your option\n[1]Start on-line game  [2]My profile [3]Exit\n",userName.c_str());
        char ch;
        while(ch=getchar(),ch<'0'||ch>'9');
        if(ch=='3')
            return 0;
        else if(ch == '2')
        {
            c.send("gtsc");
            cerr<<233;
            stringstream ss(expectRec("gtcs"));
            int myScore;
            ss>>myScore;
            cout<<"["+userName+"]:"<<endl<<"score:"+myScore<<endl;
            system("pause");

        }
        else if(ch == '1')
        {
            while(1)
            {
                int exitCode = startGame();
                if(exitCode == 1)
                {
                    printf("Error !other player disconnected ,game over\n");
                    system("pause");
                    break;
                }
                else if(exitCode == 2)
                    ;
                else if(exitCode == 0)
                    break;
            }
        }

    }
    return 0;
}
void ClientApp::welcome()
{
    system("cls");
    cout<<"+--------------------------------------------------------------+"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|              Welcome to Fight Against Landlord!!             |"<<endl
        <<"|           Resize your window to get best experience          |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"|                                                              |"<<endl
        <<"+--------------------------------------------------------------+"<<endl;
    system("pause");
}
