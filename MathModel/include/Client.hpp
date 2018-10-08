#ifndef Client_hpp
#define Client_hpp

#include <iostream>
#include <vector>
#include <cstring>
#include <sys/types.h>
#include <winsock2.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <thread>
#include <ctime>
#include <sstream>
#include "User.hpp"



class Client {
private:
    sockaddr_in server;
    //User user;

public:
    SOCKET connectSocket;
    std::string ip;
    int port;
    bool status;
    char recvBuf[1024];

    std::string to_string(int x);

    Client();

    Client(int connectSocket, sockaddr_in sockaddr);

    bool connect(std::string, int = 60000);

    bool send(std::string);

    std::string recieve();

    bool log_in(std::string, std::string);

    bool sign_up(std::string, std::string);



};

#endif
