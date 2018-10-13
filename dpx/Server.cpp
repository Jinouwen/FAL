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
    listen(serverSocket, 10);
    socklen_t len = sizeof(clientTemp);
    // running loop
    while (true) {
        if (clients.size() < 3) {
            connectSocketTemp = accept(serverSocket, (sockaddr*)&clientTemp, &len);
            // accept connection requests
            if (connectSocketTemp >= 0) {
                // wether it has already connected
                exist = false;
                for (std::vector<Client>::iterator i = clients.begin(); i != clients.end(); i++) {
                    if (i->ip == inet_ntoa(clientTemp.sin_addr)
                        //and i->port == ntohs(clientTemp.sin_port)
                        ) {
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
        }
        else std::cout << "Enough players\n";
        // respond to recieved data
        for (std::vector<Client>::iterator i = clients.begin(); i != clients.end(); i++) {
            if (!respond(*i)) {
                i->status = false;
            }
        }
        // filter out inactive clients
        filter();
    }
    return true;
}

bool Server::respond(Client &c) {
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
            if (c.user.name != "") {
                c.send("Already logged in as: " + name);
            }
            else {
                std::string findResult = userControl.find(name, pwd);
                if (findResult == "Welcome") {
                    c.user = userControl.get(name);
                    c.send("Welcome " + name);
                }
                else c.send(findResult);
            }
        }
        else if (type == "lgot") {
            std::string temp = c.user.name;
            c.user.init();
            c.send("Goodbye " + temp);
        }
        else if (type == "siup") {
            std::string name = s.substr(1, (int)s[0] - 48);
            s = s.substr(1 + (int)s[0] - 48);
            bool check = true;
            if ((name[0] < 'a' or name[0] > 'z') and (name[0] < 'A' or name[0] > 'Z')) {
                c.send("Username must begin with an letter");
                check = false;
            }
            else {
                for (int i = 0; i < s.length(); i++) {
                    if (s[i] == ' ') {
                        c.send("Username can't contain space");
                        check = false;
                    }
                }
            }
            if (check) {
                std::string pwd = s.substr(1, (int)s[0] - 48);
                if (name == "" or pwd == "") c.send("Invalid username or password");
                else {
                    std::string findResult = userControl.find(name, pwd);
                    if (findResult == "User not found") {
                        userControl.add(name, pwd);
                        c.send("User \"" + name + "\" created");
                    }
                    else c.send("User already exists");
                }
            }
            
        }
        else if (type == "prep") {
            countPlayer++;
            if (countPlayer == 3) {
                new_game();
                jow.showSituation(3);
                deal_card();
            }
        }
        else if (type == "uscd") {
            std::string winner = "";
            jow.players[c.user.id].eraseCard(Player::stringToCardSet(s));
            std::string temp;
            if (c.user.name == "") c.user.name = "user" + std::to_string(c.user.id);
            temp += c.user.name + " " + jow.players[c.user.id].CardSetToString() + "\n";
            for (std::vector<Client>::iterator i = clients.begin(); i != clients.end(); i++) {
                if (i->user.name == c.user.name) continue;
                if (i->user.name == "") i->user.name = "user" + std::to_string(i->user.id);
                temp += i->user.name + " " + std::to_string(jow.players[i->user.id].cards.size());
                if (jow.players[i->user.id].cards.size() == 0) winner = i->user.name;
            }
            c.send(temp);
            if (winner != "") {
                broadcast(winner + "wins");
                new_game();
            }
        }
        else if (type == "chet") {
            // 0: see through; 1: change card;
            
            
        }
        else if (type == "akcd") { // just for testing
            new_game();
            std::string temp;
            c.user.id = s[0] - '0';
            c.send(jow.players[c.user.id].CardSetToString());
        }
    }
    else if (len == 0) {
        return false;
    }
    return true;
}

bool Server::broadcast(std::string s) {
    bool retn = true;
    for (std::vector<Client>::iterator i = clients.begin(); i != clients.end(); i++) {
        retn &= i->send(s);
    }
    return retn;
}

void Server::deal_card() {
    for (int i = 0; i< 3; i++) {
        std::string temp;
        for (std::set<Card>::iterator j = jow.players[i].cards.begin(); j != jow.players[i].cards.end(); j++) {
            temp += std::to_string(j->id) + " ";
        }
        clients[i].user.id = i;
        clients[i].send(temp.substr(0, temp.length() - 1));
    }
}

void Server::new_game() {
    jow.dealtCards();
    countPlayer = 0;
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
    broadcast("Server has stopped");
    clients.clear();
    std::cout << "Server stopped\n";
}

Server::~Server() {
    stop();
}



