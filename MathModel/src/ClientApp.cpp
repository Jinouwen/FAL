#include "ClientApp.h"
#include "ClientMathModel.h"
ClientApp::ClientApp()
{
    //ctor
}

ClientApp::~ClientApp()
{
    //dtor
}

int ClientApp::connect()
{
    printf("Connect to Server\n");
    clock_t cStart;
    cStart = clock();
    //211.83.102.34   //192.168.1.101  // port:60000
    while (!c.connect("192.168.1.101",60000)){
        std::string s = c.recieve();
        if (s != "") {
            std::cout << s << std::endl;
        }
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
}
int ClientApp::logIn()
{
    while(1)
    {
        std::string userName,password;
        std::cerr<<"log in:"<<std::endl;
        std::cin>>userName>>password;
        c.log_in(userName,password);
        //c.log_in("jow","666");
        std::string cRec;
        while(cRec = c.recieve(),cRec == "");
        std::cerr<<"server:"+cRec<<std::endl;
        if(cRec[0]=='W'&&cRec[1]=='e') return 0;
    }
}
void ClientApp::test()
{
    ClientMathModel cmm;
    std::cerr<<"test Start"<<std::endl;


    ClientApp::logIn();
    std::string cRec;

    std::cerr<<233;
    c.send("akcd0");
    while(cRec = c.recieve(),cRec == "");
    std::cerr<<"server:"+cRec<<std::endl;
    cmm.myself.addCard(Player::stringToCardSet(cRec));
    cmm.showMyself();
    while(1)
    {
        cardSet temp = cmm.myself.choseCard();
        cmm.myself.eraseCard(temp);
        std::string toSend = Player::CardSetToString(temp);
        std::cerr<<"send"+toSend<<std::endl;
        c.use_card(toSend);
        while(cRec = c.recieve(),cRec == "");
        std::cerr<<"server:"+cRec<<std::endl;
    }



    std::cerr<<"test Done"<<std::endl;
}
