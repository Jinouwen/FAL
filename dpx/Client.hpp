#ifndef Client_hpp
#define Client_hpp

#include <iostream>
#include <vector>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <thread>
#include <ctime>
#include "User.hpp"

class Client {
private:
    sockaddr_in server;
    
public:
    int connectSocket;
    std::string ip;
    int port;
    bool status;
    char recvBuf[1024];
    User user;
    
    Client();
    
    Client(int connectSocket, sockaddr_in sockaddr);
    
    bool connect(std::string, int = 60000);
    
    bool send(std::string);
    
    std::string recieve();
    
    bool log_in(std::string, std::string);
    
    bool log_out();
    
    bool sign_up(std::string, std::string);
    
    bool ask_card();
    
    
};

#endif
