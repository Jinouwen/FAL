#include "ClientApp.h"

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
    while (!c.connect("192.168.1.101",60001)){
        if(clock()-cStart>1000)
        {
            printf(".\n");
            cStart=clock();
        }
    }
//    std::cerr<<"233"<<std::endl;
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
void ClientApp::test()
{
    std::cerr<<"test Start"<<std::endl;
    std::string toSend ="akcd";
    int nowId;
    scanf("%d",&nowId);
    toSend+=(char)('0'+nowId);
    std::cerr<<toSend;
    c.send(toSend);
    std::string msg;
    while((msg = c.recieve())=="");
    std::cerr<<msg<<std::endl;
    std::cerr<<"test Done"<<std::endl;
}
