#pragma once
#pragma comment(lib, "ws2_32.lib") 
#include <winsock2.h> 
#include <iostream>
#include "DataHandler.h"
#include "PatientRepository.h"

#pragma warning(disable: 4996)


class ConnectionListener
{
private:

    static SOCKET _connections[100];
    static int _connectionsCounter;
    static ConnectionListener* _server;
    static PatientRepository _repository;
    static std::vector<std::pair<std::pair<std::string, std::string>, SOCKET>> _accountsBase;

    SOCKET _serverSoket;
    SOCKADDR_IN _addr;
    int _sizeOfAddr;
    
    enum class Message {
        LOGIN,
        GETPATIENT, 
        LOGOUT
    };
    enum class LoginResponse {
        WRONG,
        RIGHT,
        ALREADYENTER
    };

    static void ClientHandler(int index);
    static LoginResponse LoginResponseHandler(std::string login, std::string password, SOCKET soc);
    ConnectionListener();
public:
    static ConnectionListener* GetServer();
    void Listen();
};