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
    SOCKET _serverSoket;
    static int _connectionsCounter;
    SOCKADDR_IN _addr;
    int _sizeOfAddr;
    static ConnectionListener* _server;
    static PatientRepository _repository;

    static std::vector<std::pair<std::pair<std::string, std::string>, SOCKET>> _accountsBase;
    
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
    static void ClientHandler(int index) {
        int msg_size = -1;
        Message buf;
        std::string msgResp;
        while (true) {
            int a = recv(_connections[index], (char*)&buf, sizeof(Message), NULL);
            if (a == -1) {
                std::cout << "Client " << index << " disconnected\n";
                break;
            }
            switch (buf) {
                case(Message::LOGIN):{
                    int c = recv(_connections[index], (char*)&msg_size, sizeof(int), NULL);
                    char* login = new char[msg_size + 1];
                    login[msg_size] = '\0';
                    recv(_connections[index], login, msg_size, NULL);
                    recv(_connections[index], (char*)&msg_size, sizeof(int), NULL);
                    char* password = new char[msg_size + 1];
                    password[msg_size] = '\0';
                    recv(_connections[index], password, msg_size, NULL);
                    LoginResponse resp = LoginResponseHandler(login, password, _connections[index]);
                    send(_connections[index], (char*)&resp, sizeof(LoginResponse), NULL);
                } break;
                case(Message::LOGOUT): {
                    for (size_t i = 0; i < _accountsBase.size(); i++) {
                        if (_accountsBase[i].second == _connections[index])
                            _accountsBase[i].second = 0;
                    }
                } break;
                case(Message::GETPATIENT): {
                    try {
                        msgResp = DataHandler::Packing(_repository.GetPatient());
                    }
                    catch (std::out_of_range) {
                        msgResp = "Queue is empty";
                    }
                    msg_size = msgResp.length();
                    send(_connections[index], (char*)&msg_size, sizeof(int), NULL);
                    send(_connections[index], msgResp.c_str(), msg_size, NULL);
                } break;
                default:{
                    msg_size = 5;
                    send(_connections[index], (char*)&msg_size, sizeof(int), NULL);
                    send(_connections[index], "EROR", msg_size, NULL);
                }
            }
            
        }
    }

    static LoginResponse LoginResponseHandler(std::string login, std::string password, SOCKET soc) {
        for (size_t i = 0; i < _accountsBase.size(); i++) {
            if (_accountsBase[i].first == std::pair<std::string, std::string>(login, password))
                if (_accountsBase[i].second)
                    return LoginResponse::ALREADYENTER;
                else {
                    _accountsBase[i].second = soc;
                    return LoginResponse::RIGHT;
                }
        }
        return LoginResponse::WRONG;
    }

    ConnectionListener() {
        std::pair<std::string, std::string> pair1("litvin", "123321");
        _accountsBase.push_back(std::pair<std::pair<std::string, std::string>, SOCKET>(pair1, 0));
        std::pair<std::string, std::string> pair2("platov1984", "1a2s3d");
        _accountsBase.push_back(std::pair<std::pair<std::string, std::string>, SOCKET>(pair2, 0));

        WSAData wsaData;
        WORD DLLVersion = MAKEWORD(2, 2);
        if (WSAStartup(DLLVersion, &wsaData) != 0) {
            std::cout << "Error server start\n" << std::endl;
            exit(1);

        }

        _sizeOfAddr = sizeof(_addr);
        _addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        _addr.sin_port = htons(1111);
        _addr.sin_family = AF_INET;
        _serverSoket = socket(AF_INET, SOCK_STREAM, NULL);

        bind(_serverSoket, (SOCKADDR*)&_addr, sizeof(_addr));
        Listen();
    }

public:
    
    static ConnectionListener* GetServer() {
        if (_server != nullptr) {
            return _server;
        }
        else {
            _server = new ConnectionListener();
            return _server;
        }
    }

    void Listen() {
        listen(_serverSoket, SOMAXCONN);
        std::cout << "Server is working\n";
        SOCKET newConnection;
        for (int i = 0; i < 100; i++) {
            newConnection = accept(_serverSoket, (SOCKADDR*)&_addr, &_sizeOfAddr);
            if (newConnection == 0) {
                std::cout << "Error client connect \n";
            }
            else {
                std::cout << "Client " << i << " connected\n";
                _connections[i] = newConnection;
                _connectionsCounter++;
                CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
            }
        }

    }

};



