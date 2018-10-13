#ifndef Server_hpp
#define Server_hpp

#include "Client.hpp"
#include "jow/MathModel.hpp"
#include "jow/Player.hpp"



class Server {
private:
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    int connectSocketTemp;
    sockaddr_in server, clientTemp;
    std::vector<Client> clients;
    socklen_t len;
    bool exist = false, status = false;
    UserControl userControl;
    MathModel jow;
    int countPlayer;
    
public:
    Server();
    bool run(int = 60001);
    bool respond(Client&); // recieve data and respond
    bool broadcast(std::string); // actively send msg to all
    void filter(); // delete invalid client sockets
    void stop();
    void new_game(); // inialize game variables
    void deal_card();
    ~Server();
    
};

#endif
