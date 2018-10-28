#include "Client.hpp"


std::string Client::to_string(int x)
{
    std::stringstream ss;
    ss<<x;
    std::string ans;
    ans=ss.str();
    return ans;
}
Client::Client() {

    WSADATA wsd;
    int resStartup = WSAStartup(MAKEWORD(2,2),&wsd);
    //std::cerr<<resStartup;
    connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//    fcntl(connectSocket, F_SETFL, fcntl(connectSocket, F_GETFL, 0) | O_NONBLOCK);
    int winMode = 1;
    ioctlsocket(connectSocket, FIONBIO, (u_long*)&winMode);
    memset(recvBuf, 0, sizeof(recvBuf));
    status = false;
}

Client::Client(int connectSocket, sockaddr_in sockaddr) {
    this->connectSocket = connectSocket;
    ip = inet_ntoa(sockaddr.sin_addr);
    port = ntohs(sockaddr.sin_port);
    memset(recvBuf, 0, sizeof(recvBuf));
    status = true;
}

bool Client::connect(std::string serverIp, int serverPort) {
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(serverPort);
    server.sin_addr.s_addr = inet_addr(serverIp.data());
    //std::cerr<<(
    ::connect(connectSocket, (sockaddr*)&server, sizeof(server));
    if (recieve() == "cntd" or errno == 56) {
        std::cerr << "Connected\n";
        return true;
    }
    return false;
}

bool Client::send(std::string data) {
    // pack data
    // ...
    ::send(connectSocket, data.data(), 1024, 0);
    return true;
}

std::string Client::recieve() {
    int len = (int)recv(connectSocket, recvBuf, sizeof(recvBuf), 0);
    /* value of len
     -1: recieve nothing or error occurred
     =0: client shut down the connection
     >0: length of recieved data
     */
    if (len > 0) {
        return recvBuf;
    }
    return "";
}

bool Client::log_in(std::string name, std::string pwd) {
    std::string temp = "lgin";
    temp += to_string(name.length()) + name;
    temp += to_string(pwd.length()) + pwd;
    return send(temp);
}

bool Client::sign_up(std::string name, std::string pwd) {
    std::string temp = "siup";
    temp += to_string(name.length()) + name;
    temp += to_string(pwd.length()) + pwd;
    return send(temp);
}


bool Client::log_out() {
    return send("lgot");
}

bool Client::ask_card(int id) {
    std::string temp = "akcd" + to_string(id);
    return send(temp);
}


bool Client::use_card(std::string s) {
    std::string temp = "uscd" + s;
    return send(temp);
}














