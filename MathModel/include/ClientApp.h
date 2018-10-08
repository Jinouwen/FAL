#ifndef CLIENTAPP_H
#define CLIENTAPP_H
#include <ctime>
#include "Client.hpp"

class ClientApp
{
    public:
        ClientApp();
        virtual ~ClientApp();
        int connect();
        void test();
    protected:

    private:
        Client c;
};

#endif // CLIENTAPP_H
