#ifndef CLIENTAPP_H
#define CLIENTAPP_H
#include <ctime>
#include <cstring>
#include "Client.hpp"
#include "ClientMathModel.h"

class ClientApp
{
    public:
        ClientApp();
        virtual ~ClientApp();
        int connect();
        int logIn();
        int startGame();
        int mainMenu();
        void loadWelcome();
        void welcome();
        void test();

        std::string expectRec(std::string opt);
    protected:

    private:
        Client c;
        ClientMathModel cmm;
        std::string userName,password;
};

#endif // CLIENTAPP_H
