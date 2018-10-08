#include "Server.hpp"

Server::Server() {
    memset(&server, 0, sizeof(server));
    fcntl(serverSocket, F_SETFL, fcntl(serverSocket, F_GETFL, 0) | O_NONBLOCK);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(&clientTemp, 0, sizeof(clientTemp));
    len = sizeof(clientTemp);
}

bool Server::run(int port) {
    server.sin_port = htons(port);
    std::cout << "Server starting...\n";
    while (bind(serverSocket, (sockaddr*)&server, sizeof(server))) {
        continue;
    }
    std::cout << "Server started successfully.\nWaiting for connections...\n";
    status = true;
    listen(serverSocket, 5);
    socklen_t len = sizeof(clientTemp);
    // running loop
    while (true) {
        connectSocketTemp = accept(serverSocket, (sockaddr*)&clientTemp, &len);
        // accept connection requests
        if (connectSocketTemp >= 0) {
            // wether it has already connected
            exist = false;
            for (std::vector<Client>::iterator i = clients.begin(); i != clients.end(); i++) {
                if (i->ip == inet_ntoa(clientTemp.sin_addr) and i->port == ntohs(clientTemp.sin_port)) {
                    exist = true;
                    break;
                }
            }
            if (exist) {
                std::cout << "Connection already exist: " << inet_ntoa(clientTemp.sin_addr) << ": " << ntohs(clientTemp.sin_port) << std::endl;
            }
            else {
                clients.push_back(*new Client(connectSocketTemp, clientTemp));
                clients[clients.size() - 1].send("connected");
                std::cout << "Connected from: " << inet_ntoa(clientTemp.sin_addr) << " " << ntohs(clientTemp.sin_port) << std::endl;
            }
        }
        // respond to recieved data
        for (std::vector<Client>::iterator i = clients.begin(); i != clients.end(); i++) {
            if (!respond(*i)) {
                i->status = false;
            }
        }
        filter();
    }
    return true;
}

bool Server::respond(Client c) {
    int len = (int)recv(c.connectSocket, c.recvBuf, sizeof(c.recvBuf), 0);
    std::string s = c.recvBuf, type;
    /* value of len
       -1: recieve nothing or error occurred
       =0: client shut down the connection
       >0: length of recieved data
    */
    if (len > 0) {
        type = s.substr(0, 4);
        s = s.substr(4);
        if (type == "lgin") {
            std::string name = s.substr(1, (int)s[0] - 48);
            s = s.substr(1 + (int)s[0] - 48);
            std::string pwd = s.substr(1, (int)s[0] - 48);
            std::string findResult = userControl.find(name, pwd);
            //std::cout << findResult;
            c.send(findResult);
        }
        else if (type == "siup") {
            std::string name = s.substr(1, (int)s[0] - 48);
            s = s.substr(1 + (int)s[0] - 48);
            std::string pwd = s.substr(1, (int)s[0] - 48);
            std::string findResult = userControl.find(name, pwd);
            if (findResult == "User not found") {
                userControl.add(name, pwd);
                c.send("Welcome");
            }
            else c.send("User already exists");
        }
    }
    else if (len == 0) {
        return false;
    }
    return true;
}

bool Server::broadcast(std::string type) {
    if (type == "dlcd") {
        for (std::vector<Client>::iterator i = clients.begin(); i < clients.end(); i++) {
            // deal card through jow api
        }
    }
    // else if...a
    
    return true;
}

void Server::filter() {
    int len = (int)clients.size(), i = 0;
    while (i < len) {
        if (!clients[i].status) {
            std::cout << "Connection lost: " << clients[i].ip << ", " << clients[i].port << std::endl;
            clients.erase(clients.begin() + (i--));
            len--;
        }
        i++;
    }
}

void Server::stop() {
    for (std::vector<Client>::iterator i = clients.begin(); i != clients.end(); i++) {
        i->send("Server has been cloased");
    }
        
        
    
    clients.clear();
    std::cout << "Server stopped\n";
}

Server::~Server() {
    stop();
}


